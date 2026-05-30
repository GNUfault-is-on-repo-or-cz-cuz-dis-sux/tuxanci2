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

#include "raylib.h"
#include "game/button.h"
#include "game/files.h"
#include "game/i18n.h"
#include "game/menu.h"
#include "game/screen.h"
#include "game/window.h"

/// @brief Back Button
static Button backBtn;

/// @brief Host Button
static Button hostBtn;

/// @brief Story mode Button;
static Button storymodeBtn;

/// @brief Join Button;
static Button joinBtn;

/// @brief Setup Button and play music (use in screen.c only)
void menuSetupPlay(void) {
    backBtn = buttonCreate(_("Back"), Ux(0.303f), Uy(0.75f), Uy(0.14f), Uy(0.047f));
    hostBtn = buttonCreate(_("Host Server"), Ux(0.35f), Uy(0.4f), Uy(0.15f), Uy(0.15f));
    joinBtn = buttonCreate(_("Join Game"), Ux(0.45f), Uy(0.4f), Uy(0.15f), Uy(0.15f));
    storymodeBtn = buttonCreate(_("Story Mode"), Ux(0.55f), Uy(0.4f), Uy(0.15f), Uy(0.15f));
}

/// @brief Draw Button (use in screen.c only)
void menuDrawPlay(void) {
    menuDraw(_("Play"));
    
    Vector2 pos = (Vector2){Ux(0.3f), Uy(0.235f)};
    DrawTextEx(fontSubheader, _("Select the the mode you want to play:"), pos, 24, 0, BLACK);

    buttonDraw(&backBtn);
    buttonDraw(&hostBtn);
    buttonDraw(&storymodeBtn);
    buttonDraw(&joinBtn);
}

/// @brief Update music and update Buttons
void menuUpdatePlay(void) {
    if (buttonPressed(&backBtn)) {
        menuEnter(NO_MENU);
        screenEnter(MAINMENU);
    }

    if (buttonPressed(&hostBtn))
        menuEnter(HOST);

    if (buttonPressed(&joinBtn))
        menuEnter(JOIN);

    if (buttonPressed(&storymodeBtn))
        screenEnter(STORY);
}
