
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
 * @file bg.c
 * @brief Draw the background
 */

#include "raylib.h"
#include "game/window.h"
#include "game/files.h"

/// @brief Draw the background  
void bgDraw(void) {
    Rectangle sourceRec = { 0.0f, 0.0f, (float)bg.width, (float)bg.height };
    Rectangle destRec = { 0.0f, 0.0f, (float)windowWidth, (float)windowHeight };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(bg, sourceRec, destRec, origin, 0.0f, WHITE);
}
