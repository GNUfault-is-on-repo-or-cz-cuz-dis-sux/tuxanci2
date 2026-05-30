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
 * @file camera.c
 * @brief Camera related stuff
 */

#include "raylib.h"

/// @brief Where you define the camera
Camera camera;

/// @brief Camera mode (like first person)
int cameraMode;

/// @brief Initialize the camera 
void cameraInit(void) {
    TraceLog(LOG_INFO, "Initializing camera");
    camera = (Camera){0};
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 100.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

/// @brief Update the camera 
void cameraUpdate(void) {
    UpdateCamera(&camera, cameraMode);
}
