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

/// @brief Where the arenas are loaded into
t2aMapList t2aMaps;

/// @brief Where the file is loaded into
static FILE *file;

/**
 * @brief Load a arena
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
 * @brief Decompresses and extract metadata
 * @param filename Path of the arena
 */
static arenaMetadata arenaldrGetMetadata(const char* filename) {
    arenaMetadata meta = {0};
    
    OpenFile(filename);
    if (!file) return meta;

    if (!IsFileValid()) {
        arenaldrDestroy();
        return meta;
    }

    long header_offset = ftell(file);
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, header_offset, SEEK_SET);

    size_t compressed_size = file_size - header_offset;
    void *compressed_buf = malloc(compressed_size);
    if (!compressed_buf) {
        arenaldrDestroy();
        return meta;
    }

    if (fread(compressed_buf, 1, compressed_size, file) != compressed_size) {
        free(compressed_buf);
        arenaldrDestroy();
        return meta;
    }
    arenaldrDestroy();

    unsigned long long uncompressed_size = ZSTD_getFrameContentSize(compressed_buf, compressed_size);
    if (uncompressed_size == ZSTD_CONTENTSIZE_ERROR || uncompressed_size == ZSTD_CONTENTSIZE_UNKNOWN) {
        free(compressed_buf);
        return meta;
    }

    void *uncompressed_buf = malloc(uncompressed_size);
    if (!uncompressed_buf) {
        free(compressed_buf);
        return meta;
    }

    size_t decompressed_bytes = ZSTD_decompress(uncompressed_buf, uncompressed_size, compressed_buf, compressed_size);
    free(compressed_buf);

    if (ZSTD_isError(decompressed_bytes)) {
        free(uncompressed_buf);
        return meta;
    }

    char *ptr = (char *)uncompressed_buf;

    strncpy(meta.arenaName, ptr, sizeof(meta.arenaName) - 1);
    meta.arenaName[sizeof(meta.arenaName) - 1] = '\0';
    ptr += strlen(ptr) + 1;

    strncpy(meta.arenaDesc, ptr, sizeof(meta.arenaDesc) - 1);
    meta.arenaDesc[sizeof(meta.arenaDesc) - 1] = '\0';
    ptr += strlen(ptr) + 1;

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

    free(uncompressed_buf);
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
