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
 * @file singleplayer.c
 * @brief File containing the stuff for the singleplayer menu
 */

#include "button.h"
#include "files.h"
#include "i18n.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"

/** @brief Back Button */
static Button backBtn;

/** @brief Setup Button and play music (use in screen.c only) */
void menuSetupSingleplayer(void) {
    backBtn = buttonCreate(_("Back"), 140, 650, 150, 50);
    PlayMusicStream(bgm);
}

/** @brief Draw Button (use in screen.c only) */
void menuDrawSingleplayer(void) {
    menuDraw(_("Signleplayer"));
    buttonDraw(&backBtn);
}

/** @brief Update music and update Buttons */
void menuUpdateSingleplayer(void) {
    UpdateMusicStream(bgm);

    if (buttonPressed(&backBtn)) {
        currentMenu = PLAY;
    }
}
