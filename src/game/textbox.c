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
 * @file textbox.c
 * @brief Text box system
 *
 * This file contains functions for
 * creating, drawing, updating, and
 * reading text from a text box.
 */

#include "raylib.h"
#include "game/textbox.h"
#include "game/files.h"
#include <stdbool.h>
#include <string.h>

#define CURSOR_BLINK_RATE 0.53f ///< Seconds per blink half-cycle
#define TEXT_PADDING 6          ///< Inner horizontal padding in pixels

/**
 * @brief Creates a new TextBox
 * @param x Horizontal screen position of the TextBox
 * @param y Vertical screen position of the TextBox
 * @param w Width of the TextBox
 * @param h Height of the TextBox
 * @return A TextBox struct
 */
TextBox textBoxCreate(int x, int y, int w, int h) {
    TraceLog(LOG_INFO, "Creating text box");

    TextBox t;

    t.rect = (Rectangle){(float)x, (float)y, (float)w, (float)h};
    t.buffer[0] = '\0';
    t.length = 0;
    t.fontSize = 20;
    t.focused = false;
    t.cursorTimer = 0.0f;
    t.cursorVisible = true;

    t.baseColor = (Color){230, 230, 230, 200};
    t.focusColor = (Color){230, 230, 230, 255};

    return t;
}

/**
 * @brief Draws a TextBox
 * @param t The TextBox you want to draw
 */
void textBoxDraw(TextBox *t) {
    Color bg = t->focused ? t->focusColor : t->baseColor;
    DrawRectangleRec(t->rect, bg);

    int textY = (int)(t->rect.y
                    + (t->rect.height - t->fontSize) / 2.0f);

    DrawTextEx(font, t->buffer,
               (Vector2){t->rect.x + TEXT_PADDING, (float)textY},
               (float)t->fontSize, 1.0f, BLACK);

    if (t->focused && t->cursorVisible) {
        Vector2 textSize = MeasureTextEx(
            font, t->buffer, (float)t->fontSize, 1.0f);
        int cursorX = (int)(t->rect.x + TEXT_PADDING + textSize.x) + 1;
        DrawLine(cursorX, textY,
                 cursorX, textY + t->fontSize,
                 BLACK);
    }
}

void textBoxUpdate(TextBox *t) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        t->focused = CheckCollisionPointRec(
            GetMousePosition(), t->rect);

        if (t->focused) {
            t->cursorTimer = 0.0f;
            t->cursorVisible = true;
        }
    }

    if (!t->focused) {
        return;
    }

    t->cursorTimer += GetFrameTime();
    if (t->cursorTimer >= CURSOR_BLINK_RATE) {
        t->cursorTimer = 0.0f;
        t->cursorVisible = !t->cursorVisible;
    }

    if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
            && t->length > 0) {
        t->buffer[--t->length] = '\0';
        t->cursorTimer = 0.0f;
        t->cursorVisible = true;
        return;
    }

    int ch;
    while ((ch = GetCharPressed()) != 0) {
        if (t->length >= TEXTBOX_MAX_LEN) {
            break;
        }
        t->buffer[t->length++] = (char)ch;
        t->buffer[t->length] = '\0';
        t->cursorTimer = 0.0f;
        t->cursorVisible = true;
    }
}
