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
 * @file button.c
 * @brief Button system
 *
 * This file contains functions for 
 * creating, drawing, and checking 
 * if a button has been pressed.
 */

#include "raylib.h"
#include "button.h"
#include "files.h"
#include <stdbool.h>

/**
 * @brief Creates a new Button
 * @param text Label on the Button
 * @param x Horizontal screen position of the Button
 * @param y Vertical screen position of the Button
 * @param w Width of the Button
 * @param h Height of the Button
 * @return A Button struct
 */
Button buttonCreate(const char* text, int x, int y, int w, int h) {
    Button b;
    
    b.rect = (Rectangle){
        x,
        y,
        w,
        h
    };
    
    b.text = text;
    b.fontSize = 20;
    
    // Normal color
    b.baseColor = (Color){
        200,
        200,
        200,
        200
    };
    
    // Color when hovered
    b.hoverColor = (Color){
        200,
        200,
        200,
        255
    };
    
    b.hovered = false;
    return b;
}

/**
 * @brief Draws a Button
 * @param b The Button you want to draw
 */
void buttonDraw(Button* b) {
    DrawRectangleRec(b->rect, b->hovered ? b->hoverColor : b->baseColor);

    int textWidth = MeasureText(b->text, b->fontSize);
    int textX = b->rect.x + (b->rect.width  - textWidth) / 2;
    int textY = b->rect.y + (b->rect.height - b->fontSize) / 2;

    // TODO: Make this not look like a rat's nets
    DrawTextEx(font, b->text, (Vector2){ textX, textY }, b->fontSize, 1.0f, BLACK);
}

/**
 * @brief Check if a Button is pressed
 * @param b The Button you want to check if pressed
 * @return A boolen, true if the Button was pressed, false if the Button was not pressed
 */
bool buttonPressed(Button* b) {
    Vector2 mouse = GetMousePosition();
    b->hovered = CheckCollisionPointRec(mouse, b->rect);

    bool clicked = b->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    return clicked;
}
