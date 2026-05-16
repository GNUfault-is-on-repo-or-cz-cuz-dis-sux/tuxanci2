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
 * @file old-arena-ldr.h
 * @brief Legacy arena loader
 *
 * This file contains stuff for loading legacy arenas.
 */

#ifndef OLD_ARENA_LDR_H
#define OLD_ARENA_LDR_H

/// @brief Legacy map metadata and preview image
typedef struct legacyMapMetadata {
    char name[256];
    Texture2D screen;
} legacyMapMetadata;

/// @brief List of legacy arenas
typedef struct legacyMapList {
    legacyMapMetadata arenas[64];
    int count;
} legacyMapList;

/// @brief The legacy arenas metedata and preview images are stored here
extern legacyMapList legacyMaps;

void oldarenaldrInit(void);

#endif // OLD_ARENA_LDR_H
