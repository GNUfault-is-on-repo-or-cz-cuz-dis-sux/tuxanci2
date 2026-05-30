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

#include "raylib.h"
#include "game/screen.h"
#include "game/mainmenu.h"
#include "game/menu.h"
#include "game/files.h"
#include "game/gameplay.h"
#include "game/story.h"
#include "game/loading.h"

/// @brief Set starting currentScreen
GameScreen currentScreen = LOADING;

/// @brief Draw the selected currentScreen
void screenDraw(void) {
    switch (currentScreen) {
        case MAINMENU: {
            drawMainMenu();
            break;
        }

        case MENU: {
            drawMenuScreen();
            break;
        }

        case GAMEPLAY: {
            drawGameplay();
            break;
        }

        case STORY: {
            drawStory();
            break;
        }

        case LOADING: {
            drawLoading();
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
            drawMenuScreen3D();
            break;
        }
        
        case GAMEPLAY: {
            drawGameplay3D();
            break;
        }

        case STORY: {
            drawStory3D();
            break;
        }

        case LOADING: {
            drawLoading3D();
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
        }

        case GAMEPLAY: {
            updateGameplay();
            break;
        }

        case STORY: {
            updateStory();
            break;
        }

        case LOADING: {
            updateLoading();
            break;
        }

        case NO_SCREEN:
            break;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        if (currentScreen == MAINMENU) {
            CloseWindow();
        } else {
            menuEnter(NO_MENU);
            screenEnter(MAINMENU);
            EnableCursor();
        }
    }
}

/// @brief Change screens
/// @param s The screen you want to change to
void screenEnter(GameScreen s) {
    TraceLog(LOG_INFO, "Switching screens");
    
    // Switch to the new screen
    currentScreen = s;

    // Run the selected screens init code
    switch (s) {
        case MAINMENU: {
            setupMainMenu();
            break;
        }

        case MENU: {
            setupMenuScreen();
            break;
        }

        case GAMEPLAY: {
            setupGameplay();
            break;
        }

        case STORY: {
            setupStory();
            break;
        }

        case LOADING: {
            setupLoading();
            break;
        }

        case NO_SCREEN:
            break;
    }
}
