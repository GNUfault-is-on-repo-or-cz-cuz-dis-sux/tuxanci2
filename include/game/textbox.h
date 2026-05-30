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
 * @file textbox.h
 * @brief Text box system
 *
 * This file contains functions for
 * creating, drawing, updating, and
 * reading text from a text box.
 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "raylib.h"
#include <stdbool.h>

#define TEXTBOX_MAX_LEN 255 ///< Maximum number of characters in a TextBox

/// @brief A UI TextBox
typedef struct TextBox {
    Rectangle rect;                 ///< TextBox size
    char buffer[TEXTBOX_MAX_LEN+1]; ///< Text content (null-terminated)
    int length;                     ///< Current character count
    int fontSize;                   ///< Font size
    bool focused;                   ///< Is this TextBox receiving input?
    Color baseColor;                ///< Background color when unfocused
    Color focusColor;               ///< Background color when focused
    float cursorTimer;              ///< Blink timer for the cursor
    bool cursorVisible;             ///< Is the cursor currently visible?
} TextBox;

TextBox textBoxCreate(int x, int y, int w, int h);
void textBoxDraw(TextBox *t);
void textBoxUpdate(TextBox *t);

#endif // TEXTBOX_H
