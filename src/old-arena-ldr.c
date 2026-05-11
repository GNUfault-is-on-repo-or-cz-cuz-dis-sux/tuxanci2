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
 * @file old-arena-ldr.c
 * @brief Legacy arena loader
 *
 * This file contains stuff for loading legacy arenas.
 */ 

#define _DEFAULT_SOURCE
#include <zip.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "old-arena-ldr.h"

legacyMapList legacyMaps;

static const char *src_dir = "data/arenas";
static const char *dst_root = "/tmp/tuxanci2";

/**
 * @brief Zip extractor function
 * @param zip_path The zip file you want to extract
 * @param dest_root The place you want to extract it to
 *
 * "What am I even looking at?"
 * Says the one who wrote it
 */ 
static void extract_zip(const char *zip_path, const char *dest_root) {
    int err = 0;
    struct zip *z = zip_open(zip_path, 0, &err);
    if (!z) return;

    char folder_name[256];
    const char *last_slash = strrchr(zip_path, '/');
    const char *base = last_slash ? last_slash + 1 : zip_path;
    strncpy(folder_name, base, sizeof(folder_name));
    char *dot = strrchr(folder_name, '.');
    if (dot) *dot = '\0';

    char target_path[512];
    snprintf(target_path, sizeof(target_path), "%s/%s", dest_root, folder_name);
    mkdir(target_path, 0755);

    zip_int64_t num_entries = zip_get_num_entries(z, 0);
    for (zip_int64_t i = 0; i < num_entries; i++) {
        struct zip_stat st;
        zip_stat_index(z, i, 0, &st);

        char out_file_path[1024];
        snprintf(out_file_path, sizeof(out_file_path), "%s/%s", target_path, st.name);

        struct zip_file *f = zip_fopen_index(z, i, 0);
        if (f) {
            FILE *out = fopen(out_file_path, "wb");
            if (out) {
                char buf[8192];
                zip_int64_t n;
                while ((n = zip_fread(f, buf, sizeof(buf))) > 0) {
                    fwrite(buf, 1, n, out);
                }
                fclose(out);
            }
            zip_fclose(f);
        }
    }
    zip_close(z);
}

/** 
 * @brief Reads title and processes the preview image 
 * @param folder_path The path to the extracted arena folder
 */
static legacyMapMetadata oldarenaldrGetArenaMetadata(const char* folder_path) {
    legacyMapMetadata meta = {0};
    char map_path[512];
    char screen_filename[256] = {0};
    
    snprintf(map_path, sizeof(map_path), "%s/arena.map", folder_path);

    FILE* f = fopen(map_path, "r");
    if (!f) return meta;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "name ", 5) == 0) {
            strncpy(meta.name, line + 5, sizeof(meta.name) - 1);
            meta.name[strcspn(meta.name, "\r\n")] = 0;
        }
        
        if (strncmp(line, "screen ", 7) == 0) {
            strncpy(screen_filename, line + 7, sizeof(screen_filename) - 1);
            screen_filename[strcspn(screen_filename, "\r\n")] = 0;
        }
    }
    fclose(f);

    if (strlen(screen_filename) > 0) {
        char img_path[512];
        snprintf(img_path, sizeof(img_path), "%s/%s", folder_path, screen_filename);

        Image fullImg = LoadImage(img_path);
        
        if (fullImg.data != NULL) {
            Rectangle rightHalfRec = { 
                (float)fullImg.width / 2,
                0,
                (float)fullImg.width / 2,
                (float)fullImg.height
            };
            
            Image rightHalfImg = ImageFromImage(fullImg, rightHalfRec);
            
            ImageResize(&rightHalfImg, 320, 240);
            
            meta.screen = LoadTextureFromImage(rightHalfImg);

            UnloadImage(fullImg);
            UnloadImage(rightHalfImg);
        }
    }

    return meta;
}

/** @brief Load all legacy arenas metadata and preview images */
static legacyMapList oldarenaldrLoadAllMetadata(void) {
    legacyMapList list = {0};

    DIR *dir = opendir(dst_root);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && list.count < 64) {
        if (entry->d_name[0] == '.') continue;

        if (entry->d_type == DT_DIR) {
            char folder_path[512];
            snprintf(folder_path, sizeof(folder_path), "%s/%s", dst_root, entry->d_name);

            list.arenas[list.count] = oldarenaldrGetArenaMetadata(folder_path);
            
            if (strlen(list.arenas[list.count].name) > 0) {
                list.count++;
            }
        }
    }

    closedir(dir);
    return list;
}

/** @brief Extract the legacy maps */
void oldarenaldrInit(void) {
    mkdir(dst_root, 0755);

    DIR *dir = opendir(src_dir);
    if (!dir) return;
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".zip")) {
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", src_dir, entry->d_name);
            extract_zip(full_path, dst_root);
        }
    }

    closedir(dir);

    legacyMaps = oldarenaldrLoadAllMetadata();
}

