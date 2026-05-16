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
 * @file screen.h
 * @brief Screen system
 */

#ifndef SCREEN_H
#define SCREEN_H

/// @brief Diffrent screens you can go to
typedef enum {
    NO_SCREEN, ///< Blank screen
    MAINMENU,  ///< Main menu (the inital screen)
    MENU,      ///< Menu (used when a menu window is on the screen)
    GAMEPLAY   ///< When the game is well.. playing
} GameScreen;

void screenUpdate(void);
void screenDraw(void);
void screenDraw3D(void);
void screenEnter(GameScreen s);

#endif // SCREEN_H
