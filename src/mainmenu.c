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

#include "button.h"
#include "files.h"
#include "i18n.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "bgm.h"
#include "window.h"
#include "bg.h"

/// @brief Play Button
static Button playBtn;

/// @brief Quit Button
static Button quitBtn;

#include <stdio.h>

/// @brief Setup Buttons and play music (use in screen.c only)
void setupMainMenu(void) {
    playBtn = buttonCreate(_("Play"), Ux(0.15f), Uy(0.5f), Uy(0.14f), Uy(0.047f));
    quitBtn = buttonCreate(_("Quit"), Ux(0.15f), Uy(0.56f), Uy(0.14f), Uy(0.047f));

    bgmPlay();
}

/// @brief Draw background and Buttons (use in screen.c only)
void drawMainMenu(void) {
    bgDraw();

    buttonDraw(&playBtn);
    buttonDraw(&quitBtn);
}

/// @brief Unused
void drawMainMenu3D(void) {}

/// @brief Update music and update Buttons (use in screen.c only)
void updateMainMenu(void) {
#ifdef ENABLE_DEBUG
    if(IsKeyPressed(KEY_D))
        menuEnter(DEBUG);
#endif // ENABLE_DEBUG

    if (buttonPressed(&playBtn))
        menuEnter(PLAY);

    // FIXME: This just does a segfault for some reason.
    if (buttonPressed(&quitBtn))
        CloseWindow();
}
