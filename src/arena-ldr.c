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

#include "raylib.h"
#include "arena-ldr.h"
#include <zstd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

/// @brief How many bytes the magic number is
#define MAGIC_NUMBER_BYTES 3

/// @brief Location of the arena files
#define SRC_DIR "data/arenas"

/// @brief Background image dimensions
#define BG_WIDTH 4096
#define BG_HEIGHT 3072

/// @brief Music details
#define MUSIC_SAMPLE_RATE 44100
#define MUSIC_SAMPLE_SIZE 8
#define MUSIC_CHANNELS 2

/// @brief Current Arena
arenaAssets currentArena;

/// @brief Where the arenas are loaded into
t2aMapList t2aMaps;

/// @brief Where the file is loaded into
static FILE *file;

/**
 * @brief Load an arena file
 * @param filename Path of the file
 */
void OpenFile(const char *filename) {
    file = fopen(filename, "rb");
}

/**
 * @brief Check if the loaded file is valid
 * @returns Returns true if valid, false if not
 */
bool IsFileValid(void) {
    if (!file) return false;

    const char MagicNumber[] = {'T', '2', 'A'};
    char buffer[MAGIC_NUMBER_BYTES];

    rewind(file);
    if (fread(buffer, 1, MAGIC_NUMBER_BYTES, file) != MAGIC_NUMBER_BYTES) {
        return false;
    }

    if (memcmp(MagicNumber, buffer, MAGIC_NUMBER_BYTES) == 0) {
        fseek(file, 4, SEEK_SET);
        return true;
    } else {
        return false;
    }
}

/// @brief Unload file
void arenaldrDestroy(void) {
    if (file) {
        fclose(file);
        file = NULL;
    }
}

/**
 * @brief Decompresses and extract arenas
 * @param filename Path of the arena
 */
static void *DecompressArena(const char *filename, size_t *out_size) {
    OpenFile(filename);
    if (!file) return NULL;

    if (!IsFileValid()) {
        arenaldrDestroy();
        return NULL;
    }

    long header_offset = ftell(file);
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, header_offset, SEEK_SET);

    size_t compressed_size = (size_t)(file_size - header_offset);
    void *compressed_buf = malloc(compressed_size);
    if (!compressed_buf) {
        arenaldrDestroy();
        return NULL;
    }

    if (fread(compressed_buf, 1, compressed_size, file) != compressed_size) {
        free(compressed_buf);
        arenaldrDestroy();
        return NULL;
    }
    arenaldrDestroy();

    unsigned long long uncompressed_size = ZSTD_getFrameContentSize(compressed_buf, compressed_size);
    if (uncompressed_size == ZSTD_CONTENTSIZE_ERROR ||
        uncompressed_size == ZSTD_CONTENTSIZE_UNKNOWN) {
        free(compressed_buf);
        return NULL;
    }

    void *uncompressed_buf = malloc(uncompressed_size);
    if (!uncompressed_buf) {
        free(compressed_buf);
        return NULL;
    }

    size_t decompressed_bytes = ZSTD_decompress(
        uncompressed_buf, uncompressed_size,
        compressed_buf, compressed_size
    );
    free(compressed_buf);

    if (ZSTD_isError(decompressed_bytes)) {
        free(uncompressed_buf);
        return NULL;
    }

    *out_size = (size_t)decompressed_bytes;
    return uncompressed_buf;
}

/**
 * @brief Decompresses and extracts metadata
 * @param filename Path of the arena
 */
static arenaMetadata arenaldrGetMetadata(const char *filename) {
    arenaMetadata meta = {0};

    size_t data_size = 0;
    void *data = DecompressArena(filename, &data_size);
    if (!data) return meta;

    char *ptr = (char *)data;
    char *end = ptr + data_size;

    strncpy(meta.arenaName, ptr, sizeof(meta.arenaName) - 1);
    meta.arenaName[sizeof(meta.arenaName) - 1] = '\0';
    ptr += strlen(ptr) + 1;
    if (ptr >= end) { free(data); return meta; }

    strncpy(meta.arenaDesc, ptr, sizeof(meta.arenaDesc) - 1);
    meta.arenaDesc[sizeof(meta.arenaDesc) - 1] = '\0';
    ptr += strlen(ptr) + 1;
    if (ptr >= end) { free(data); return meta; }

    Image img = {
        .data = (void *)ptr,
        .width = 800,
        .height = 600,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };

    if (img.data != NULL) {
        meta.arenaImage = LoadTextureFromImage(img);
    }

    free(data);
    return meta;
}

/// @brief Initialize and load all arenas
void arenaldrInit(void) {
    DIR *dir = opendir(SRC_DIR);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && t2aMaps.count < 64) {
        if (entry->d_name[0] == '.') continue;

        if (strstr(entry->d_name, ".t2a")) {
            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", SRC_DIR, entry->d_name);

            struct stat st;
            if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)) {
                arenaMetadata meta = arenaldrGetMetadata(full_path);
                if (strlen(meta.arenaName) > 0) {
                    t2aMaps.arenas[t2aMaps.count] = meta;
                    t2aMaps.count++;
                }
            }
        }
    }

    closedir(dir);
}

/**
 * @brief Load the gameplay assets for the arena at the given index.
 * @param index Index into t2aMaps
 * @returns Populated arenaAssets, or zeroed struct on failure
 */
arenaAssets arenaldrGameplay(int index) {
    arenaAssets assets = {0};

    if (index < 0 || index >= t2aMaps.count) return assets;

    char full_path[PATH_MAX];
    DIR *dir = opendir(SRC_DIR);
    if (!dir) return assets;

    int found = 0;
    int current = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        if (!strstr(entry->d_name, ".t2a")) continue;

        char candidate[PATH_MAX];
        snprintf(candidate, sizeof(candidate), "%s/%s", SRC_DIR, entry->d_name);

        struct stat st;
        if (stat(candidate, &st) != 0 || !S_ISREG(st.st_mode)) continue;

        if (current == index) {
            snprintf(full_path, sizeof(full_path), "%s", candidate);
            found = 1;
            break;
        }
        current++;
    }
    closedir(dir);

    if (!found) return assets;

    size_t data_size = 0;
    void *data = DecompressArena(full_path, &data_size);
    if (!data) return assets;

    unsigned char *ptr = (unsigned char *)data;
    unsigned char *end = ptr + data_size;

    ptr += strlen((char *)ptr) + 1;
    if (ptr >= end) { free(data); return assets; }

    ptr += strlen((char *)ptr) + 1;
    if (ptr >= end) { free(data); return assets; }

    size_t thumbnail_bytes = 800 * 600 * 3;
    if (ptr + thumbnail_bytes + 1 > end) { free(data); return assets; }
    ptr += thumbnail_bytes;

    if (*ptr != 0x00) { free(data); return assets; }
    ptr++;
    if (ptr >= end) { free(data); return assets; }

    unsigned char *music_start = ptr;
    while (ptr < end && !(*ptr == 0x00 && (ptr == music_start || *(ptr - 1) != 0x00))) {
        ptr++;
    }

    if (ptr >= end) { free(data); return assets; }

    size_t music_bytes = (size_t)(ptr - music_start);
    ptr++;
    if (ptr >= end) { free(data); return assets; }

    size_t bg_bytes = (size_t)BG_WIDTH * BG_HEIGHT * 3;
    if (ptr + bg_bytes > end) { free(data); return assets; }

    Image bg_img = {
        .data = (void *)ptr,
        .width = BG_WIDTH,
        .height = BG_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    };
    assets.background = LoadTextureFromImage(bg_img);

    void *pcm_copy = malloc(music_bytes);
    if (!pcm_copy) {
        UnloadTexture(assets.background);
        assets.background = (Texture2D){0};
        free(data);
        return assets;
    }
    memcpy(pcm_copy, music_start, music_bytes);
    assets.musicPCM = pcm_copy;
    assets.musicPCMSize = music_bytes;

    assets.musicStream = LoadAudioStream(MUSIC_SAMPLE_RATE, MUSIC_SAMPLE_SIZE, MUSIC_CHANNELS);

    free(data);
    return assets;
}

/**
 * @brief Unload all gameplay assets.
 * @param assets Pointer to the arenaAssets to clean up
 */
void arenaldrUnloadAssets(arenaAssets *assets) {
    if (!assets) return;

    if (assets->background.id != 0) {
        UnloadTexture(assets->background);
        assets->background = (Texture2D){0};
    }

    if (IsAudioStreamValid(assets->musicStream)) {
        StopAudioStream(assets->musicStream);
        UnloadAudioStream(assets->musicStream);
        assets->musicStream = (AudioStream){0};
    }

    if (assets->musicPCM) {
        free(assets->musicPCM);
        assets->musicPCM = NULL;
        assets->musicPCMSize = 0;
    }
}