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
 * @file screen.c
 * @brief Screen system
 *
 * This file contains the stuff for
 * switching between screens.
 */

#include "screen.h"
#include "mainmenu.h"
#include "menu.h"
#include "files.h"
#include "raylib.h"

/// @brief Set starting currentScreen
GameScreen currentScreen = NO_SCREEN;

/// @brief Draw the selected currentScreen
void screenDraw(void) {
    switch (currentScreen) {
        case MAINMENU: {
            ClearBackground(BLACK);
            drawMainMenu();
            break;
        }
        case MENU: {
            ClearBackground(BLACK);
            drawMenuScreen();
            break;
        }
        case NO_SCREEN:
            break;
    }
}

/// @brief Draw the 3D scene of the selected currentScreen
void screenDraw3D(void) {
    switch (currentScreen) {
        case MAINMENU: {
            drawMainMenu3D();
            break;
        }
        case MENU: {
            drawMenuScreen();
            break;
        }
        case NO_SCREEN:
            break;
    }
}

/// @brief Update the selected currentScreen
void screenUpdate(void) {
    switch (currentScreen) {
        case MAINMENU: {
            updateMainMenu();
            break;
        }
        case MENU: {
            updateMenuScreen();
            break;
        case NO_SCREEN:
            break;
        }
    }
}

/// @brief Change screens
/// @param s The screen you want to change to
void screenEnter(GameScreen s) {
    // Switch to the new screen
    currentScreen = s;

    // Run the selected screens init code
    switch (s) {
        case MAINMENU:
            setupMainMenu();
            enterMainMenu();
            break;

        case MENU:
            setupMenuScreen();
            enterMenuScreen();
            break;

        case NO_SCREEN:
            break;
    }
}
