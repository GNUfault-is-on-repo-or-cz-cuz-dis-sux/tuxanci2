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
 * @file music.c
 * @brief Arena music streaming
 */

#include "raylib.h"
#include "arena-ldr.h"
#include <string.h>
#include <stdint.h>

static bool IsMusicPlaying = false;
static size_t musicCursor = 0;

/// @brief Audio thread callback
static void MusicStreamCallback(void *buffer, unsigned int frames) {
    if (!IsMusicPlaying || currentArena.musicPCM == NULL || currentArena.musicPCMSize == 0) {
        memset(buffer, 128, frames * 2);
        return;
    }

    unsigned char *out = (unsigned char *)buffer;
    unsigned char *pcm = (unsigned char *)currentArena.musicPCM;
    size_t total = currentArena.musicPCMSize;
    size_t needed = (size_t)frames * 2;
    size_t written = 0;

    while (written < needed) {
        if (musicCursor >= total) musicCursor = 0;
        size_t chunk = needed - written;
        size_t remaining = total - musicCursor;
        if (chunk > remaining) chunk = remaining;
        memcpy(out + written, pcm + musicCursor, chunk);
        musicCursor += chunk;
        written += chunk;
    }
}

/// @brief Play the selected arena's music 
void musicPlay(void) {
    musicCursor = 0;
    IsMusicPlaying = false;

    if (!IsAudioStreamValid(currentArena.musicStream)) return;
    if (currentArena.musicPCM == NULL || currentArena.musicPCMSize == 0) return;

    SetAudioStreamCallback(currentArena.musicStream, MusicStreamCallback);
    PlayAudioStream(currentArena.musicStream);
    IsMusicPlaying = true;
}

/// @brief Stop the selected arena's music 
void musicStop(void) {
    if (IsAudioStreamValid(currentArena.musicStream)) {
        StopAudioStream(currentArena.musicStream);
        SetAudioStreamCallback(currentArena.musicStream, NULL);
    }
    IsMusicPlaying = false;
    musicCursor = 0;
}
