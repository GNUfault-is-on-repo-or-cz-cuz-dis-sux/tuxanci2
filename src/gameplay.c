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

#include "raylib.h"
#include "raymath.h"
#include "screen.h"
#include "bgm.h"
#include "camera.h"
#include "files.h"
#include "window.h"

static float yaw = 0.0f;
static float pitch = 0.0f;
static Vector3 lookDir = { 0.0f, 0.0f, -1.0f };
static float playerY = 1.8f;
static float velocityY = 0.0f;
static const float gravity = -0.4f;
static const float jumpStrength = 0.15f;

void setupGameplay(void) {
    bgmStop();
    DisableCursor();
}

void drawGameplay(void) {
    ClearBackground(SKYBLUE);
}

void drawGameplay3D(void) {
    DrawPlane((Vector3){0,0,0}, (Vector2){128,128}, GRAY);
    DrawModel(tux, (Vector3){0,0,0}, 0.061f, WHITE);
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

    Vector3 forward = lookDir;
    forward.y = 0;
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

    Vector3 move = (Vector3){0};

    if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);
    if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);

    if (Vector3Length(move) > 0.01f)
        move = Vector3Scale(Vector3Normalize(move), speed);

    camera.position.x += move.x;
    camera.position.z += move.z;

    if (IsKeyPressed(KEY_SPACE) && playerY <= 1.8f + 0.001f)
        velocityY = jumpStrength;

    velocityY += gravity * GetFrameTime();
    playerY += velocityY;

    if (playerY < 1.8f) {
        playerY = 1.8f;
        velocityY = 0.0f;
    }

    camera.position.y = playerY;

    float half = 64.0f;

    if (camera.position.x < -half) camera.position.x = -half;
    if (camera.position.x > half) camera.position.x = half;
    if (camera.position.z < -half) camera.position.z = -half;
    if (camera.position.z > half) camera.position.z = half;

    camera.target = Vector3Add(camera.position, lookDir);
}
