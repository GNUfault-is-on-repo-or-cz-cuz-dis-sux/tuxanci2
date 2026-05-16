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

#include <unistd.h>
#include "addon.h"
#include "files.h"
#include "i18n.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "old-arena-ldr.h"
#include "arena-ldr.h"
#include "config.h"
#include "bgm.h"

#define WINDOW_WIDTH 1024        ///< Window width
#define WINDOW_HEIGHT 768        ///< Window height
#define WINDOW_FPS 60            ///< Window FPS
#define WINDOW_TITLE "Tuxánci 2" ///< Window title

/// @brief Program entry
int main(void) {
    // Internationalization setup
    setlocale(LC_ALL, "");
    bindtextdomain("tuxanci2", "locale");
    textdomain("tuxanci2");

    SetTraceLogLevel(LOG_WARNING);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(WINDOW_FPS);

    InitAudioDevice();
    
    if (access(configFile, F_OK) != 0) {
        configDefaults();
    }

    commonLoad();

    addonInit();

    arenaldrInit();
    oldarenaldrInit();

    screenEnter(MAINMENU);

    // Main loop
    while (!WindowShouldClose()) {
        screenUpdate();
        menuUpdate();
        bgmUpdate();

        BeginDrawing();
        ClearBackground(BLACK);
        screenDraw();
        screenDraw3D();
        EndMode3D();
        EndDrawing();
    }

    configDestroy();
    commonDestroy();
    CloseWindow();

    return 0;
}
