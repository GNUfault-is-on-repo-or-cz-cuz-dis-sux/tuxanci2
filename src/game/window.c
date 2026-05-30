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
 * @file window.c
 * @brief Get window width and height
 */

#include "raylib.h"
#include "game/main.h"

#define WINDOW_TITLE "Tuxánci 2" ///< Window title

/// @brief The width of the window
int windowWidth;

/// @brief The height of the window
int windowHeight;

/// @brief What monitor the window is on
int windowMonitor;

/// @brief The target fps of the window 
int windowFPS;

/// @brief Initialize the window
/// @param title Title of the window
void windowInit() {
    TraceLog(LOG_INFO, "Initializing window");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1, 1, WINDOW_TITLE);
    ToggleFullscreen();
    SetExitKey(KEY_NULL);
}

/// @brief Updates windowWidth and windowHeight
void windowUpdate(void) {
    windowWidth = GetScreenWidth();
    windowHeight = GetScreenHeight();
    windowMonitor = GetCurrentMonitor();
    windowFPS = GetMonitorRefreshRate(windowMonitor);
    SetTargetFPS(windowFPS);
}

/// @brief Close the window 
void windowClose(void) {
    mainDestroy();
}

/**
 * @brief Turn percents into a x coordinate
 * @param percent Percent on the x axis
 * @return Actual x coordinate
 */
float Ux(float percent) {
    return percent * windowWidth;
}

/**
 * @brief Turn percents into a y coordinate
 * @param percent Percent on the y axis
 * @return Actual y coordinate
 */
float Uy(float percent) {
    return percent * windowHeight;
}
