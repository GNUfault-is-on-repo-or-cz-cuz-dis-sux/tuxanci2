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
 * @file gameplay.c
 * @brief Gameplay related stuff
 */

#include "raylib.h"
#include "screen.h"
#include "bgm.h"
#include "arena-ldr.h"
#include "music.h"

/// @brief Start gameplay (use in screen.c only) 
void setupGameplay(void) {
    bgmStop();
  
    currentArena = arenaldrGameplay(0);
  
    musicPlay();
}

/// @brief Draw gameplay (use in screen.c only) 
void drawGameplay(void) {
    if (currentArena.background.id != 0) {
        DrawTexturePro(
            currentArena.background,
            (Rectangle){ 0, 0, currentArena.background.width, currentArena.background.height },
            (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    }
}

// Both unused for now (both will be used later)
void drawGameplay3D(void) {}
void updateGameplay(void) {}
