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
 * @file list.h
 * @brief List system
 */

#ifndef LIST_H
#define LIST_H

#include "raylib.h"
#include <stdbool.h>

#define LIST_MAX_ITEMS 64   ///< Maximum number of items in a List
#define LIST_ITEM_HEIGHT 30 ///< Height of each item row in pixels

typedef struct List {
    Rectangle rect;                  ///< List bounds
    char items[LIST_MAX_ITEMS][128]; ///< Item name strings
    int itemCount;                   ///< Number of items currently in the list
    int selectedIndex;               ///< Index of the selected item (-1 if none)
    int fontSize;                    ///< Font size for item text
    Color baseColor;                 ///< Background color
    Color selectedColor;             ///< Color of the selected item
    Color hoverColor;                ///< Color of a hovered item
    int hoveredIndex;                ///< Index of the currently hovered item (-1 if none)
} List;

List listCreate(int x, int y, int w, int h);
void listDraw(List* l);
bool listCheck(List* l);
bool listAdd(List* l, const char* name);
bool listRemove(List* l, const char* name);

#endif // LIST_H