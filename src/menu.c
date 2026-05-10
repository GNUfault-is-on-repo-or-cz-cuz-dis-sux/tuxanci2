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
 * @file menu.c
 * @brief Menu system
 *
 * This file contains the stuff for menus.
 */

#include "menu.h"
#include "files.h"
#include "mainmenu.h"
#include "play.h"
#include "raylib.h"
#include "screen.h"

/** @brief Set the starting menu */
GameMenu currentMenu = NO_MENU;

/** @brief Setup menu screen (only use in screen.h) */
void setupMenuScreen(void) { menuSetupPlay(); }

/** @brief Update/Tick menu */
void menuUpdate(void) {
    if (currentMenu != NO_MENU) {
        currentScreen = MENU;
    }
}

/**
 * @brief Draw menu window
 * @param title Title of the menu window
 */
void menuDraw(const char* title) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int rectWidth = 800;
    int rectHeight = 600;

    Color color = WHITE;

    int posX = (screenWidth - rectWidth) / 2;
    int posY = (screenHeight - rectHeight) / 2;

    int size = 40;
    int spacing = 5;

    DrawRectangle(posX, posY, rectWidth, rectHeight + size, color);

    DrawTexture(explosions, posX, posY - size - spacing, WHITE);

    Vector2 pos = (Vector2){posX + spacing, posY - size - spacing};

    DrawTextEx(font, title, pos, size, 0, color);
}

/** @brief Draw menu screen (use only in screen.c) */
void drawMenuScreen(void) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawTexture(bg, 0, 0, WHITE);

    DrawRectangleGradientV(0, 0, width, height, Fade(BLACK, 0.5f),
                           Fade(BLACK, 1.0f));

    switch (currentMenu) {
    case PLAY: {
        menuDrawPlay();
    }
    case NO_MENU:
        break;
    }
}

/** @brief Unused */
void drawMenuScreen3D(void) {}

/** @brief Unused */
void enterMenuScreen(void) {}

/** @brief Update menu screen (use only in screen.c) */
void updateMenuScreen(void) {
    UpdateMusicStream(bgm);

    switch (currentMenu) {
    case PLAY: {
        menuUpdatePlay();
    }
    case NO_MENU:
        break;
    }
}
