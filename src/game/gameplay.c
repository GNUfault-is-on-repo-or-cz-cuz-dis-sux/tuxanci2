/*
 * Tuxánci 2 - Successor to Tuxánci
 * Copyright (C) 2026  Connor Thomson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file gameplay.c
 * @brief Gameplay related stuff
 */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "game/screen.h"
#include "game/bgm.h"
#include "game/camera.h"
#include "game/files.h"
#include "game/window.h"
#include "core/network.h"
#include "core/server.h"

typedef struct {
    uint32_t client_id;
    float x, y, z;
    float yaw, pitch;
    int active;
} RemotePlayer;

static RemotePlayer g_remotePlayers[MAX_CLIENTS];

static char g_serverHost[64] = "127.0.0.1";
static int g_serverPort = 2201;
static int g_isHost = 1;

void gameplaySetServer(const char *host, int port) {
    strncpy(g_serverHost, host, sizeof(g_serverHost) - 1);
    g_serverPort = port;
    g_isHost = 0;
}

static float yaw = 0.0f;
static float pitch = 0.0f;
static Vector3 lookDir = { 0.0f, 0.0f, -1.0f };
static float playerY = 1.8f;
static float velocityY = 0.0f;
static float lastYaw = 0.0f;
static float lastPitch = 0.0f;
static const float gravity = -0.4f;
static const float jumpStrength = 0.15f;

static int g_sock = -1;
static uint32_t g_clientId = 0;
static struct sockaddr_in g_server;
static sem_t g_serverReady;

Model plane;

static void *serverThread(void *arg) {
    (void)arg;
    serverInit(g_serverPort);
    sem_post(&g_serverReady);
    while (1) serverUpdate();
    serverDestroy();
    return NULL;
}

static void netConnect(void) {
    g_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (g_sock < 0) { perror("socket"); return; }

    memset(&g_server, 0, sizeof(g_server));
    g_server.sin_family = AF_INET;
    g_server.sin_port = htons(g_serverPort);
    inet_pton(AF_INET, g_serverHost, &g_server.sin_addr);

    if (g_isHost)
        sem_wait(&g_serverReady);

    struct ConnectPacket pkt = { .magic = CONNECT_MAGIC };
    sendto(g_sock, &pkt, sizeof(pkt), 0,
           (struct sockaddr*)&g_server, sizeof(g_server));

    struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };
    setsockopt(g_sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    uint8_t buf[64];
    ssize_t n = recv(g_sock, buf, sizeof(buf), 0);
    if (n == (ssize_t)sizeof(struct ConnectedPacket)) {
        struct ConnectedPacket *reply = (struct ConnectedPacket*)buf;
        if (reply->magic == CONNECTED_MAGIC) {
            g_clientId = reply->client_id;
        }
    }

    tv.tv_sec = tv.tv_usec = 0;
    setsockopt(g_sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}

static void netSendMove(float x, float y, float z, float yw, float pt) {
    if (g_sock < 0 || g_clientId == 0) return;

    struct MovePacket pkt = {
        .magic = MOVE_MAGIC,
        .client_id = g_clientId,
        .x = x, .y = y, .z = z,
        .yaw = yw, .pitch = pt
    };
    sendto(g_sock, &pkt, sizeof(pkt), 0,
           (struct sockaddr*)&g_server, sizeof(g_server));
}

static void netPoll(void) {
    if (g_sock < 0) return;

    uint8_t buf[256];
    ssize_t n;
    while ((n = recv(g_sock, buf, sizeof(buf), MSG_DONTWAIT)) > 0) {

        if (n == (ssize_t)sizeof(struct MoveAckPacket)) {
            // reconciliation stub
        }

        if (n == (ssize_t)sizeof(struct PlayerStatePacket)) {
            struct PlayerStatePacket *s = (struct PlayerStatePacket*)buf;
            if (s->magic != PLAYER_STATE_MAGIC) continue;

            RemotePlayer *slot = NULL;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (g_remotePlayers[i].active &&
                    g_remotePlayers[i].client_id == s->client_id) {
                    slot = &g_remotePlayers[i];
                    break;
                }
            }
            if (!slot) {
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (!g_remotePlayers[i].active) {
                        slot = &g_remotePlayers[i];
                        slot->active = 1;
                        slot->client_id = s->client_id;
                        break;
                    }
                }
            }
            if (slot) {
                slot->x = s->x;
                slot->y = s->y;
                slot->z = s->z;
                slot->yaw = s->yaw;
                slot->pitch = s->pitch;
            }
        }
    }
}

static void netDisconnect(void) {
    if (g_sock >= 0) {
        close(g_sock);
        g_sock = -1;
        g_clientId = 0;
    }
}

void setupGameplay(void) {
    memset(g_remotePlayers, 0, sizeof(g_remotePlayers));

    bgmStop();
    DisableCursor();
    cameraMode = CAMERA_FIRST_PERSON;

    Mesh mesh = GenMeshPlane(128.0f, 128.0f, 1, 1);
    plane = LoadModelFromMesh(mesh);

    Image img = LoadImageFromTexture(ground);
    ImageMipmaps(&img);
    Texture2D ground2 = LoadTextureFromImage(img);
    UnloadImage(img);

    plane.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = ground2;

    if (g_isHost) {
        sem_init(&g_serverReady, 0, 0);
        pthread_t server;
        pthread_create(&server, NULL, serverThread, NULL);
        pthread_detach(server);
    }

    netConnect();
}

/// @brief Unused
void drawGameplay(void) {
    int size = 24;

    DrawLine(Ux(0.5f) - size, Uy(0.5f), Ux(0.5f) - size / 4, Uy(0.5f), RED);
    DrawLine(Ux(0.5f) + size / 4, Uy(0.5f), Ux(0.5f) + size, Uy(0.5f), RED);
    DrawLine(Ux(0.5f), Uy(0.5f) - size, Ux(0.5f), Uy(0.5f) - size / 4, RED);
    DrawLine(Ux(0.5f), Uy(0.5f) + size / 4, Ux(0.5f), Uy(0.5f) + size, RED);
}

void drawGameplay3D(void) {
    rlDisableBackfaceCulling();
        DrawModelEx(
            sky,
            (Vector3){0, 0, 0},
            (Vector3){1, 0, 0},
            90.0f,
            (Vector3){256.0f, 256.0f, 256.0f},
            WHITE
        );
    rlEnableBackfaceCulling();

    DrawModel(plane, (Vector3){0, 0, 0}, 1.0f, WHITE);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!g_remotePlayers[i].active) continue;

        RemotePlayer *p = &g_remotePlayers[i];
        Vector3 pos = { p->x, p->y - 1.8f, p->z };

        DrawModelEx(tux, pos,
                    (Vector3){0, 1, 0},
                    p->yaw * RAD2DEG,
                    (Vector3){0.061f, 0.061f, 0.061f},
                    WHITE);

        Vector2 screenPos = GetWorldToScreen(
            (Vector3){p->x, p->y + 0.4f, p->z}, camera);
        DrawText(TextFormat("id=%u\nx=%.1f y=%.1f z=%.1f\nyaw=%.2f pitch=%.2f",
                            p->client_id,
                            p->x, p->y, p->z,
                            p->yaw, p->pitch),
                 (int)screenPos.x, (int)screenPos.y, 10, WHITE);
    }
}

void updateGameplay(void) {
    float speed = 0.2f;

    Vector2 mouse = GetMouseDelta();
    yaw -= mouse.x * 0.003f;
    pitch -= mouse.y * 0.003f;

    if (pitch > 1.5f) pitch = 1.5f;
    if (pitch < -1.5f) pitch = -1.5f;

    lookDir.x = cosf(pitch) * sinf(yaw);
    lookDir.y = sinf(pitch);
    lookDir.z = cosf(pitch) * cosf(yaw);
    lookDir = Vector3Normalize(lookDir);

    Vector3 forward = lookDir; forward.y = 0;
    forward = Vector3Normalize(forward);
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

    Vector3 move = {0};
    if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);

    bool hasMoved = Vector3Length(move) > 0.01f;
    if (hasMoved)
        move = Vector3Scale(Vector3Normalize(move), speed);

    camera.position.x += move.x;
    camera.position.z += move.z;

    if (IsKeyPressed(KEY_SPACE) && playerY <= 1.8f + 0.001f)
        velocityY = jumpStrength;

    velocityY += gravity * GetFrameTime();
    playerY += velocityY;

    if (playerY < 1.8f) { playerY = 1.8f; velocityY = 0.0f; }

    camera.position.y = playerY;

    float half = 64.0f;
    if (camera.position.x < -half) camera.position.x = -half;
    if (camera.position.x > half) camera.position.x = half;
    if (camera.position.z < -half) camera.position.z = -half;
    if (camera.position.z > half) camera.position.z = half;

    camera.target = Vector3Add(camera.position, lookDir);

    bool hasRotated = fabsf(yaw - lastYaw) > 0.001f ||
                      fabsf(pitch - lastPitch) > 0.001f;
    lastYaw = yaw;
    lastPitch = pitch;

    if (hasMoved || velocityY != 0.0f || hasRotated)
        netSendMove(camera.position.x, camera.position.y, camera.position.z,
                    yaw, pitch);

    netPoll();
}

void destroyGameplay(void) {
    netDisconnect();
    if (g_isHost) sem_destroy(&g_serverReady);
    g_isHost = 1;
    strncpy(g_serverHost, "127.0.0.1", sizeof(g_serverHost));
    g_serverPort = 2201;
    EnableCursor();
}
