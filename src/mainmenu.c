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
#include "button.h"
#include "files.h"
#include "menu.h"
#include "screen.h"
#include "addon.h"

/** @brief Play Button */
static Button playBtn;

/** @brief Add-on Button */
static Button addonBtn;

/** @brief Quit Button */
static Button quitBtn;

/** @brief Setup Buttons and play music (use in screen.c only) */
void setupMainMenu(void) {
    playBtn  = buttonCreate("Play", 200, 300, 150, 50);
    addonBtn = buttonCreate("Add-ons", 200, 360, 150, 50);
    quitBtn  = buttonCreate("Quit", 200, 420, 150, 50);

    PlayMusicStream(bgm);
}

/** @brief Draw background and Buttons (use in screen.c only) */
void drawMainMenu(void) {
    float scale = (float)GetScreenWidth() / bg.width;
    DrawTextureEx(bg, (Vector2){ 0, 0 }, 0.0f, scale, WHITE);

    buttonDraw(&playBtn);
    buttonDraw(&addonBtn);
    buttonDraw(&quitBtn);
}

/** @brief Unused */
void drawMainMenu3D(void) {}

/** @brief Unused */
void enterMainMenu(void) {}

/** @brief Update music and check if buttons are pressed/hovered (use in screen.c only) */
void updateMainMenu(void) {
    UpdateMusicStream(bgm);

    if(buttonPressed(&playBtn)) {
        currentMenu = PLAY;
    }

    if(buttonPressed(&addonBtn)) {
        addonPick();
    } 

    if(buttonPressed(&quitBtn)) {
        // FIXME: This just does a segfault for some reason, prob a memory leak or whatever
        CloseWindow();
    }
}
