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
 * @file mainmenu.h
 * @brief Loads and stores data in RAM from files.
 */

#ifndef FILES_H
#define FILES_H

#include "raylib.h"

extern Texture2D bg;
extern Texture2D logo;
extern Font font;
extern Font fontHeader;
extern Font fontSubheader;
extern Music bgm;
extern Texture2D explosions;
extern Model tux;
extern ModelAnimation *tuxanims;
extern unsigned int tuxanimCount;
extern Sound tuxtalk;
extern Sound sting;
extern Model nolok;
extern Sound noloktalk;

void commonLoad(void);
void commonDestroy(void);

#endif // FILES_H
