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
 * @file bgm.c
 * @brief Plays the background music on the mainmenu and menus
 */

#include "raylib.h"
#include "files.h"

/// @brief Play background music 
void bgmPlay(void) {
    PlayMusicStream(bgm);
}

/// @brief Update background music (needs to be called every frame, but I already do that in main.c)  
void bgmUpdate(void) {
    UpdateMusicStream(bgm);
}

/// @brief Stop the background music
void bgmStop(void) {
    StopMusicStream(bgm);
}
