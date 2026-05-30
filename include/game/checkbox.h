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

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "raylib.h"
#include <stdbool.h>

/// @brief A UI Checkbox
typedef struct Checkbox {
    Rectangle rect;     ///< Checkbox size
    bool state;         ///< Checkbox state
    bool hovered;       ///< Is mouse over Button?
    Color baseColor;    ///< Button color
    Color checkedColor; ///< Button color (checked)
} Checkbox;

Checkbox checkboxCreate(int x, int y);
void checkboxDraw(Checkbox* b);
bool checkboxPressed(Checkbox* b);

#endif // CHECKBOX_H
