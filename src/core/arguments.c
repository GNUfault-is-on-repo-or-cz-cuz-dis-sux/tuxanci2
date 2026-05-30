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
 * @file arguments.c
 * @brief Stores command line arguments
 */

#ifndef ENABLE_SERVER
#   include "raylib.h"
#else
#   include <stdio.h>
#endif // ENABLE_SERVER

/// @brief Argument count
int argumentCount;

/// @brief Argument vector
const char **argumentVector;

/**
 * @brief Stores command line arguments globaly
 * @param argc Input for argumentCount
 * @param argv Input for argumentVector
 */
void argumentsStore(int argc, char *argv[]) {
#ifndef ENABLE_SERVER
    TraceLog(LOG_INFO, "Storing arguments");
#else
#   ifdef ENABLE_DEBUG
        puts("INFO: Storing arguments");
#   endif // ENABLE_DEBUG
#endif // ENABLE_SERVER

    argumentCount = argc;
    argumentVector = (const char **)argv;
}
