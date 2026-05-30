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
 * @file server.c
 * @brief tuxanci2 game server
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "core/network.h"

static int g_serverSock = -1;
static uint32_t g_nextClientId = 1;

typedef struct {
    uint32_t client_id;
    struct sockaddr_in addr;
    socklen_t addrLen;
    float x, y, z;
    float yaw, pitch;
    int active;
} ClientSlot;

static ClientSlot g_clients[MAX_CLIENTS];

void serverInit(int port) {
    memset(g_clients, 0, sizeof(g_clients));

    g_serverSock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(g_serverSock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        return;
    }
}

static ClientSlot *findSlot(uint32_t id) {
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (g_clients[i].active && g_clients[i].client_id == id)
            return &g_clients[i];
    return NULL;
}

static ClientSlot *allocSlot(void) {
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (!g_clients[i].active)
            return &g_clients[i];
    return NULL;
}

static void broadcastState(ClientSlot *moved) {
    struct PlayerStatePacket state = {
        .magic = PLAYER_STATE_MAGIC,
        .client_id = moved->client_id,
        .x = moved->x, .y = moved->y, .z = moved->z,
        .yaw = moved->yaw, .pitch = moved->pitch
    };

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!g_clients[i].active) continue;
        if (g_clients[i].client_id == moved->client_id) continue;

        sendto(g_serverSock, &state, sizeof(state), 0,
               (struct sockaddr*)&g_clients[i].addr, g_clients[i].addrLen);
    }
}

void serverUpdate(void) {
    uint8_t buffer[1024];

    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    int n = recvfrom(g_serverSock, buffer, sizeof(buffer), 0,
                     (struct sockaddr*)&client, &len);

    if (n <= 0) return;

    if (n == sizeof(struct ConnectPacket)) {
        struct ConnectPacket *pkt = (struct ConnectPacket*)buffer;

        if (pkt->magic == CONNECT_MAGIC) {
            ClientSlot *slot = allocSlot();
            if (!slot) return;

            slot->active = 1;
            slot->client_id = g_nextClientId++;
            slot->addr = client;
            slot->addrLen = len;
            slot->x = slot->y = slot->z = 0;
            slot->yaw = slot->pitch = 0;

            struct ConnectedPacket w = {
                .magic = CONNECTED_MAGIC,
                .client_id = slot->client_id
            };

            sendto(g_serverSock, &w, sizeof(w), 0,
                   (struct sockaddr*)&client, len);

            return;
        }
    }

    if (n == sizeof(struct MovePacket)) {
        struct MovePacket *pkt = (struct MovePacket*)buffer;

        if (pkt->magic == MOVE_MAGIC) {
            ClientSlot *slot = findSlot(pkt->client_id);
            if (!slot) return;

            slot->x = pkt->x;
            slot->y = pkt->y;
            slot->z = pkt->z;
            slot->yaw = pkt->yaw;
            slot->pitch = pkt->pitch;

            struct MoveAckPacket ack = {
                .magic = MOVE_ACK_MAGIC,
                .client_id = pkt->client_id,
                .x = pkt->x, .y = pkt->y, .z = pkt->z,
                .yaw = pkt->yaw, .pitch = pkt->pitch,
                .sequence = 0
            };
            sendto(g_serverSock, &ack, sizeof(ack), 0,
                   (struct sockaddr*)&client, len);

            broadcastState(slot);
            return;
        }
    }
}

void serverDestroy(void) {
    if (g_serverSock >= 0) {
        close(g_serverSock);
        g_serverSock = -1;
    }
}