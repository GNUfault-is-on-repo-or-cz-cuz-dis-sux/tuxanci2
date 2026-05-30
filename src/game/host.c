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
 * @file host.c
 * @brief File containing the stuff for the host menu
 */

#include "raylib.h"
#include "game/button.h"
#include "game/files.h"
#include "game/i18n.h"
#include "game/list.h"
#include "game/menu.h"
#include "game/screen.h"
#include "game/desc.h"
#include "game/window.h"
#include "core/server.h"
#include "game/bg.h"

/// @brief Back Button
static Button backBtn;

/// @brief Start Button;
static Button startBtn;

/// @brief Legacy map list
static List mapList;

/// @brief Setup Button, list, and play music (use in screen.c only)
void menuSetupHost(void) {
    backBtn = buttonCreate(_("Back"), Ux(0.303f), Uy(0.75f), Uy(0.14f), Uy(0.047f));
    startBtn = buttonCreate(_("Start"), Ux(0.618f), Uy(0.75f), Uy(0.14f), Uy(0.047f));

    mapList = listCreate(Ux(0.31f), Uy(0.235f), Uy(0.25f), Uy(0.5f));
}

/// @brief Draw Button, map list, and preview image (use in screen.c only)
void menuDrawHost(void) {
    menuDraw(_("Host Server"));
    buttonDraw(&backBtn);
    buttonDraw(&startBtn);
    listDraw(&mapList);
}

/// @brief Update music, list, and Buttons
void menuUpdateHost(void) {
    listCheck(&mapList);

    if (buttonPressed(&backBtn))
        menuEnter(PLAY);

    if (buttonPressed(&startBtn))
        screenEnter(GAMEPLAY);
}
