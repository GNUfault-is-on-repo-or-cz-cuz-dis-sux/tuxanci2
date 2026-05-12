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
 * @file checkbox.c
 * @brief Checkbox system
 *
 * This file contains functions for
 * creating, drawing, and checking
 * if a checkbox has been pressed.
 */

#include "checkbox.h"
#include "files.h"
#include "raylib.h"
#include <stdbool.h>

/**
 * @brief Creates a new Checkbox
 * @param x Horizontal screen position of the Checkbox
 * @param y Vertical screen position of the Checkbox
 * @return A Checkbox struct
 */
Checkbox checkboxCreate(int x, int y) {
    Checkbox c;
    c.rect = (Rectangle){(float)x, (float)y, 20.0f, 20.0f}; 
    c.state = false;
    
    c.baseColor = RED;
    c.checkedColor = GREEN;
    
    return c;
}

/**
 * @brief Draws a Checkbox
 * @param b The Checkbox you want to draw
 */
void checkboxDraw(Checkbox* b) {
    DrawRectangleRec(b->rect, b->state ? b->checkedColor : b->baseColor);
}

/**
 * @brief Check if a Checkbox is pressed
 * @param b The Checkbox you want to check if pressed
 * @return A boolean, true if the Checkbox was pressed,
 * false if the Checkbox was not pressed.
 */
bool checkboxPressed(Checkbox* b) {
    Vector2 mouse = GetMousePosition();
    
    if (CheckCollisionPointRec(mouse, b->rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        b->state = !b->state;
        return true;
    }
    
    return false;
}