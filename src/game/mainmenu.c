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
 * @file mainmenu.c
 * @brief Main menu
 *
 * This file contains the stuff for
 * the main menu, like the buttons,
 * music, background, etc.
 */

#include "raylib.h"
#include "game/button.h"
#include "game/files.h"
#include "game/i18n.h"
#include "game/menu.h"
#include "game/screen.h"
#include "game/bgm.h"
#include "game/window.h"
#include "game/bg.h"

/// @brief Play Button
static Button playBtn;

/// @brief Quit Button
static Button quitBtn;

/// @brief Internel function for drawing the logo 
static void logoDraw(void) {
    DrawTexture(logo, Ux(0.1f), Uy(0.1f), WHITE);
}

/// @brief Setup Buttons and play music (use in screen.c only)
void setupMainMenu(void) {
    playBtn = buttonCreate(_("Play"), Ux(0.15f), Uy(0.5f), Uy(0.14f), Uy(0.047f));
    quitBtn = buttonCreate(_("Quit"), Ux(0.15f), Uy(0.56f), Uy(0.14f), Uy(0.047f));

    bgmPlay();
}

/// @brief Draw background and Buttons (use in screen.c only)
void drawMainMenu(void) {
    bgDraw();
    logoDraw();

    buttonDraw(&playBtn);
    buttonDraw(&quitBtn);
}

/// @brief Unused
void drawMainMenu3D(void) {}

/// @brief Update music and update Buttons (use in screen.c only)
void updateMainMenu(void) {
    if (buttonPressed(&playBtn))
        menuEnter(PLAY);

    if (buttonPressed(&quitBtn))
        windowClose();
}
