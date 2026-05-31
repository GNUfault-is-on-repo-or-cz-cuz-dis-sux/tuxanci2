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
#include "game/screen.h"

/// @brief The background
Texture2D bg;

/// @brief The logo
Texture2D logo;

/// @brief Font (20pt)
Font font;

/// @brief Font (40pt)
Font fontHeader;

/// @brief Font (24pt)
Font fontSubheader;

/// @brief The background music
Music bgm;

/// @brief The image used on the header bar on the menus
Texture2D explosions;

/// @brief Tux
Model tux;

/// @brief Tux animations
ModelAnimation *tuxanims;

/// @brief Tux animations count
unsigned int tuxanimCount;

/// @brief Tux talking sound
Sound tuxtalk;

/// @brief Misc story sounds
Sound sting;

/// @brief Nolok
Model nolok;

/// @brief Nolok talking sound
Sound noloktalk;

/// @brief The sky
Model sky;

/// @brief The ground
Texture2D ground;

/// @brief Load files into RAM
void commonLoad(void) {    
    TraceLog(LOG_INFO, "Loading all assets");
    bg = LoadTexture("data/common/images/menu.png");
    logo = LoadTexture("data/common/images/logo.png");
    font = LoadFontEx("/usr/share/fonts/dejavu/DejaVuSans.ttf", 20, 0, 0);
    fontHeader = LoadFontEx("/usr/share/fonts/dejavu/DejaVuSans.ttf", 40, 0, 0);
    fontSubheader = LoadFontEx("/usr/share/fonts/dejavu/DejaVuSans.ttf", 24, 0, 0);
    bgm = LoadMusicStream("data/common/music/menu.ogg");
    explosions = LoadTexture("data/menu/images/explosions.jpg");
    tux = LoadModel("data/gameplay/models/tux.glb");
    tuxanims = LoadModelAnimations("data/gameplay/models/tux.glb", &tuxanimCount);
    tuxtalk = LoadSound("data/story/sounds/tux.wav");
    sting = LoadSound("data/story/sounds/sting.wav");
    nolok = LoadModel("data/gameplay/models/nolok.glb");
    noloktalk = LoadSound("data/story/sounds/nolok.wav");
    sky = LoadModel("data/gameplay/models/sky.glb");
    ground = LoadTexture("data/gameplay/images/ground.png");
}

/// @brief Free files in RAM
void commonDestroy(void) {
    TraceLog(LOG_INFO, "Unloading all assets");
    UnloadTexture(bg);
    UnloadTexture(logo);
    UnloadFont(font);
    UnloadFont(fontHeader);
    UnloadFont(fontSubheader);
    UnloadMusicStream(bgm);
    UnloadTexture(explosions);
    UnloadModel(tux);
    //UnloadModelAnimations(tuxanims);
    UnloadSound(tuxtalk);
    UnloadSound(sting);
    UnloadModel(nolok);
    UnloadSound(noloktalk);
    UnloadModel(sky);
    UnloadTexture(ground);
}
