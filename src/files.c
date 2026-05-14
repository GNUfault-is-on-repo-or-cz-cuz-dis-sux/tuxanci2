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

/// @brief The background
Texture2D bg;

/// @brief The fonts
Font font;
Font fontHeader;
Font fontSubheader;

/// @brief The background music
Music bgm;

/// @brief Menu sounds
Sound hover;
Sound back;
Sound menuopen;
Sound menuclose;
Sound select;

/// @brief The image used on the header bar on the menus
Texture2D explosions;

/// @brief Load files into RAM
void commonLoad(void) {
    /* 
     * I know it doesn’t adhear to the conventions to
     * do this but just look at how clean it looks!!!
     */
    bg            = LoadTexture("data/common/images/main.jpg");
    font          = LoadFontEx("/usr/share/fonts/dejavu/DejaVuSans.ttf", 20, 0, 0);
    fontHeader    = LoadFontEx("/usr/share/fonts/dejavu/DejaVuSans.ttf", 40, 0, 0);
    fontSubheader = LoadFontEx("/usr/share/fonts/dejavu/DejaVuSans.ttf", 24, 0, 0);
    bgm           = LoadMusicStream("data/common/music/menu.ogg");
    hover         = LoadSound("data/common/sounds/hover.wav");
    back          = LoadSound("data/common/sounds/back.wav");
    menuopen      = LoadSound("data/common/sounds/open.wav");
    menuclose     = LoadSound("data/common/sounds/close.wav");
    select        = LoadSound("data/common/sounds/select.wav");
    explosions    = LoadTexture("data/menu/images/explosions.jpg");
}

/// @brief Free files in RAM
void commonDestroy(void) {
    UnloadTexture(bg);
    UnloadFont(font);
    UnloadFont(fontHeader);
    UnloadFont(fontSubheader);
    UnloadMusicStream(bgm);
    UnloadSound(hover);
    UnloadSound(back);
    UnloadSound(menuopen);
    UnloadSound(menuclose);
    UnloadSound(select);
    UnloadTexture(explosions);
}
