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
 * @file files.c
 * @brief Loads and stores data in RAM from files.
 *
 * I perfer to load everything into 
 * RAM at once as they are fairly small
 * and makes it more fast once its done
 * loading.
 */

#include "raylib.h"
#include "screen.h"

/** @brief The background */
Texture2D bg;

/** @brief The main font */
Font font;

/** @brief The background music */
Music bgm;

/** @brief The image used on the header bar on the menus */
Texture2D explosions;

/** @brief Load files into RAM */
void commonLoad(void) {    
    bg         = LoadTexture("common/images/main.jpg");
    font       = LoadFont("common/fonts/font.ttf");
    bgm        = LoadMusicStream("common/music/menu.ogg");
    explosions = LoadTexture("menu/images/explosions.jpg");
}

/** @brief Free files in RAM */
void commonDestroy(void) {
    UnloadTexture(bg);
    UnloadFont(font);
    UnloadMusicStream(bgm);
    UnloadTexture(explosions);
}