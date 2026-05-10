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
#include "screen.h"
#include "mainmenu.h"
#include "menu.h"

/** @brief Set starting currentScreen */
GameScreen currentScreen = MAINMENU;

/** @brief Draw the selected currentScreen */
void screenDraw(void) {
    switch(currentScreen) {
        case MAINMENU:
            ClearBackground(BLACK);
            drawMainMenu();
            break;
        case MENU:
            ClearBackground(BLACK);
            drawMenuScreen();
    }
}

/** @brief Draw the 3D scene of the selected currentScreen */
void screenDraw3D(void) {
    switch(currentScreen) {
        case MAINMENU: {
            drawMainMenu3D();
            break;
        }
        case MENU: {
            drawMenuScreen();
            break;
        }
    }
}

/** @brief Update the selected currentScreen */
void screenUpdate(void) {
    switch (currentScreen) {
        case MAINMENU: {
            static bool mainmenuRan = false;
            if (!mainmenuRan) {
                setupMainMenu();
                enterMainMenu();
                mainmenuRan = true;
            }
            updateMainMenu();
            break;
        }
        case MENU: {
            static bool menuRan = false;
            if(!menuRan) {
                setupMenuScreen();
                enterMenuScreen();
                menuRan = true;
            }
            updateMenuScreen();
            break;
        }
    }
}