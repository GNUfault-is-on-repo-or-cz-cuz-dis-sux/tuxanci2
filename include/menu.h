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
 * @file menu.h
 * @brief Menu system
 */

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include "raylib.h"

typedef enum {
    NO_MENU, ///< No menu
    PLAY     ///< Play menu
} GameMenu;

extern GameMenu currentMenu;

void menuUpdate(void);
void menuDraw(const char* title);

void setupMenuScreen(void);
void drawMenuScreen(void);
void drawMenuScreen3D(void);
void enterMenuScreen(void);
void updateMenuScreen(void);

#endif // MENU_SCREEN_H
