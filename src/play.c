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
 * @file play.c
 * @brief File containing the stuff for the play menu
 */

#include "button.h"
#include "files.h"
#include "i18n.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "window.h"

/// @brief Back Button
static Button backBtn;

/// @brief Singleplayer Button
static Button singleplayerBtn;

/// @brief Setup Button and play music (use in screen.c only)
void menuSetupPlay(void) {
    backBtn = buttonCreate(_("Back"), Ux(0.303f), Uy(0.75f), Uy(0.14f), Uy(0.047f));
    singleplayerBtn = buttonCreate(_("Singleplayer"), Ux(0.45f), Uy(0.4f), Uy(0.15f), Uy(0.15f));
}

/// @brief Draw Button (use in screen.c only)
void menuDrawPlay(void) {
    menuDraw(_("Play"));
    
    Vector2 pos = (Vector2){Ux(0.3f), Uy(0.235f)};
    DrawTextEx(fontSubheader, _("Select the the mode you want to play:"), pos, 24, 0, BLACK);

    buttonDraw(&backBtn);
    buttonDraw(&singleplayerBtn);
}

/// @brief Update music and update Buttons
void menuUpdatePlay(void) {
    if (buttonPressed(&backBtn)) {
        menuEnter(NO_MENU);
        screenEnter(MAINMENU);
    }
    if (buttonPressed(&singleplayerBtn)) {
        menuEnter(SINGLEPLAYER);
    }
}
