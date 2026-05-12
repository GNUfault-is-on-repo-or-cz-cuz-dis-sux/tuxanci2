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
 * @file config.c
 * @brief Writing and reading config files
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// @brief Config file path stored here
char* configFile = NULL;

/// @brief Init the config path 
void configInit(void) {
    const char *home = getenv("HOME");
    const char *file = ".tuxanci2.cfg";
    
    if (!home) return;

    configFile = malloc(strlen(home) + strlen(file) + 2);
    if (configFile) {
        sprintf(configFile, "%s/%s", home, file);
    }
}

/// @brief Clean up config stuff  
void configDestroy(void) {
    free(configFile);
}

/**
 * @brief Read config file
 * @param entry Entry to read from config file
 * @returns Contents of the entry in the config file
 */
char* configRead(const char* entry) {
    FILE* file = fopen("~/.tuxanci2.cfg", "r");
    if (file == NULL) {
        return NULL;
    }

    char line[256];
    char* value = NULL;

    while (fgets(line, sizeof(line), file)) {
        char* keyPos = strstr(line, entry);
        
        if (keyPos != NULL) {
            char* sep = strchr(line, '=');
            if (sep != NULL) {
                char* valStart = sep + 1;

                while (isspace((unsigned char)*valStart)) valStart++;

                char* valEnd = valStart + strlen(valStart) - 1;
                while (valEnd > valStart && isspace((unsigned char)*valEnd)) {
                    *valEnd = '\0';
                    valEnd--;
                }

                value = strdup(valStart);
                break;
            }
        }
    }

    fclose(file);
    return value;
}

/**
 * @brief Write to config file
 * @param entry Entry to write to
 * @param data What to put in the entry
 */
void configWrite(const char* entry, const char* data) {
    const char* filename = "~/.tuxanci2.cfg";
    char **lines = NULL;
    size_t line_count = 0;
    int found = 0;

    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char *current_line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&current_line, &len, file)) != -1) {
            lines = realloc(lines, sizeof(char*) * (line_count + 1));

            if (!found && strncmp(current_line, entry, strlen(entry)) == 0 && 
               (current_line[strlen(entry)] == ' ' || current_line[strlen(entry)] == '=')) {
                
                asprintf(&lines[line_count], "%s = %s\n", entry, data);
                found = 1;
                free(current_line);
                current_line = NULL;
            } else {
                lines[line_count] = current_line;
                current_line = NULL;
            }
            line_count++;
        }
        free(current_line);
        fclose(file);
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        for (size_t i = 0; i < line_count; i++) free(lines[i]);
        free(lines);
        return;
    }

    for (size_t i = 0; i < line_count; i++) {
        fputs(lines[i], file);
        free(lines[i]);
    }

    if (!found) {
        fprintf(file, "%s = %s\n", entry, data);
    }

    fclose(file);
    free(lines);
}

/// @brief Create default config
void configDefaults(void) {
    configWrite("MUTE", "false");
}