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
 * @file main.c
 * @brief Main file
 *
 * This file sets up the window, audio,
 * and it includes the main loop and
 * some other random stuff.
 */


#include "raylib.h"
#include "game/files.h"
#include "game/i18n.h"
#include "game/menu.h"
#include "game/screen.h"
#include "game/config.h"
#include "game/bgm.h"
#include "game/window.h"
#include "game/camera.h"
#include "core/arguments.h"
#include "core/watchdog.h"
#include "game/client.h"
#include <stdlib.h>

static void mainInit(int argc, char *argv[]) {
#ifndef ENABLE_DEBUG
    SetTraceLogLevel(LOG_WARNING);
#endif // ENABLE_DEBUG

    argumentsStore(argc, argv);
    
    i18nInit();

    windowInit();
    
    // Update once before we need to display anything
    windowUpdate();
    screenUpdate();

    InitAudioDevice();
    
    commonLoad();

    configInit();

    screenEnter(MAINMENU);

    cameraInit();

    clientInit();

    watchdogInit(argv[0]);

    clientConnect("127.0.0.1", 2201);
}

static void mainUpdate(void) {
    windowUpdate();
    screenUpdate();
    menuUpdate();
    bgmUpdate();
    cameraUpdate();
    watchdogUpdate();
}

static void mainDraw(void) {
    ClearBackground(BLACK);
    screenDraw();
}

static void mainDraw3D(void) {
    screenDraw3D();
}

/// @brief Unload and exit (no return)
void mainDestroy(void) {
    TraceLog(LOG_INFO, "Exiting");
    configDestroy();
    commonDestroy();
    clientDestroy();
    CloseWindow();
    exit(0);
}

/// @brief Program entry
int main(int argc, char *argv[]) {
    mainInit(argc, argv);

    while (!WindowShouldClose()) {
        mainUpdate();

        BeginDrawing();
            mainDraw();
           
            BeginMode3D(camera);
                mainDraw3D();
            EndMode3D();
        EndDrawing();
    }

    mainDestroy();
}
