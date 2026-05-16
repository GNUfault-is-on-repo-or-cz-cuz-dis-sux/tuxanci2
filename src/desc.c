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
 * @file desc.c
 * @brief Description box stuff
 */

#include "raylib.h"
#include "files.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Draw text box
 * @param x X coordinate
 * @param y Y coordinate
 * @param w Width
 * @param h Height
 * @param description 
 */
void descDraw(int x, int y, int w, int h, const char *description) {
    if (!description) return;

    int fontSize = 20;
    int lineSpacing = 24;
    int currentX = x;
    int currentY = y;

    Color color = (Color){230, 230, 230, 200};
    DrawRectangle(x, y, w, h, color);

    char *textCopy = strdup(description);
    if (!textCopy) return;

    Vector2 spaceSize = MeasureTextEx(font, " ", (float)fontSize, 1.0f);

    char *word = strtok(textCopy, " ");
    while (word != NULL) {
        Vector2 wordSize = MeasureTextEx(font, word, (float)fontSize, 1.0f);
        int wordWidth = (int)wordSize.x;

        if (currentX + wordWidth > x + w) {
            currentX = x;
            currentY += lineSpacing;
        }

        if (currentY + fontSize > y + h) {
            break;
        }

        Vector2 position = { (float)currentX, (float)currentY };
        DrawTextEx(font, word, position, (float)fontSize, 1.0f, BLACK);

        currentX += wordWidth + (int)spaceSize.x;

        word = strtok(NULL, " ");
    }

    free(textCopy);
}
