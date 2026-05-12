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
 * @file list.c
 * @brief List system
 *
 * This file contains functions for
 * creating, drawing, and interacting
 * with a scrollable item list.
 */

#include "list.h"
#include "files.h"
#include "raylib.h"
#include <stdbool.h>
#include <string.h>

/**
 * @brief Creates a new List
 * @param x Horizontal screen position of the List
 * @param y Vertical screen position of the List
 * @param w Width of the List
 * @param h Height of the List
 * @return A List struct
 */
List listCreate(int x, int y, int w, int h) {
    List l;

    l.rect = (Rectangle){x, y, w, h};

    l.itemCount = 0;
    l.selectedIndex = -1;
    l.hoveredIndex = -1;
    l.fontSize = 20;

    l.baseColor = (Color){230, 230, 230, 255};

    l.selectedColor = (Color){253, 170, 72, 255};
    
    return l;
}

/**
 * @brief Draws a List
 * @param l The List you want to draw
 */
void listDraw(List* l) {
    DrawRectangleRec(l->rect, l->baseColor);

    for (int i = 0; i < l->itemCount; i++) {
        Rectangle itemRect = {
            l->rect.x,
            l->rect.y + i * LIST_ITEM_HEIGHT,
            l->rect.width,
            LIST_ITEM_HEIGHT
        };

        if (itemRect.y + LIST_ITEM_HEIGHT > l->rect.y + l->rect.height)
            break;

        Color rowColor = l->baseColor;
        if (i == l->selectedIndex)
            rowColor = l->selectedColor;

        DrawRectangleRec(itemRect, rowColor);

        int textY = itemRect.y + (LIST_ITEM_HEIGHT - l->fontSize) / 2;
        DrawTextEx(font, l->items[i],
                   (Vector2){itemRect.x + 6, textY},
                   l->fontSize, 1.0f, BLACK);
    }
}

/**
 * @brief Checks if an item in the List was clicked
 * @param l The List you want to check
 * @return true if a new item was selected, false otherwise
 */
bool listCheck(List* l) {
    Vector2 mouse = GetMousePosition();
    l->hoveredIndex = -1;

    for (int i = 0; i < l->itemCount; i++) {
        Rectangle itemRect = {
            l->rect.x,
            l->rect.y + i * LIST_ITEM_HEIGHT,
            l->rect.width,
            LIST_ITEM_HEIGHT
        };

        if (itemRect.y + LIST_ITEM_HEIGHT > l->rect.y + l->rect.height)
            break;

        if (CheckCollisionPointRec(mouse, itemRect)) {
            l->hoveredIndex = i;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                l->selectedIndex = i;
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Adds an item to a List
 * @param l The List to add to
 * @param name The name of the item to add
 * @return true if the item was added, false if the List is full
 */
bool listAdd(List* l, const char* name) {
    if (l->itemCount >= LIST_MAX_ITEMS)
        return false;

    strncpy(l->items[l->itemCount], name, sizeof(l->items[0]) - 1);
    l->items[l->itemCount][sizeof(l->items[0]) - 1] = '\0';
    l->itemCount++;

    return true;
}

/**
 * @brief Removes an item from a List
 * @param l The List to remove from
 * @param name The name of the item to remove
 * @return true if the item was found and removed, false if it was not found
 */
bool listRemove(List* l, const char* name) {
    for (int i = 0; i < l->itemCount; i++) {
        if (strcmp(l->items[i], name) == 0) {
            for (int j = i; j < l->itemCount - 1; j++)
                strncpy(l->items[j], l->items[j + 1], sizeof(l->items[0]));

            l->itemCount--;

            if (l->selectedIndex == i)
                l->selectedIndex = -1;
            else if (l->selectedIndex > i)
                l->selectedIndex--;

            if (l->hoveredIndex > i)
                l->hoveredIndex--;

            return true;
        }
    }

    return false;
}