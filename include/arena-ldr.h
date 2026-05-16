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
 * @file arena-ldr.c
 * @brief Arena loader
 *
 * This file contains stuff for loading arenas.
 */

#ifndef ARENA_LDR_H
#define ARENA_LDR_H

#include "raylib.h"
#include <stdbool.h>

/// @brief Arena metadata
typedef struct arenaMetadata {
    char arenaName[128];
    char arenaDesc[128];
    Texture2D arenaImage;
} arenaMetadata;

/// @brief List of all the maps
typedef struct t2aMapList {
    arenaMetadata arenas[64];
    int count;
} t2aMapList;

/// @brief Where the arenas are loaded into
extern t2aMapList t2aMaps;

void arenaldrInit(void);
void OpenFile(const char *filename);
bool IsFileValid(void);
void arenaldrDestroy(void);

#endif // ARENA_LDR_H