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
 * @file join.c
 * @brief File containing the stuff for the join menu
 */

#include <stdlib.h>
#include "raylib.h"
#include "game/button.h"
#include "game/i18n.h"
#include "game/menu.h"
#include "game/screen.h"
#include "game/textbox.h"
#include "game/window.h"
#include "game/gameplay.h"
#include "game/files.h"

static Button backBtn;
static Button startBtn;
static TextBox ipBox;
static TextBox portBox;

void menuSetupJoin(void) {
    backBtn = buttonCreate(_("Back"),  Ux(0.303f), Uy(0.75f), Uy(0.14f), Uy(0.047f));
    startBtn = buttonCreate(_("Start"), Ux(0.618f), Uy(0.75f), Uy(0.14f), Uy(0.047f));

    ipBox = textBoxCreate(Ux(0.35f), Uy(0.42f), Ux(0.30f), Uy(0.055f));
    portBox = textBoxCreate(Ux(0.35f), Uy(0.50f), Ux(0.30f), Uy(0.055f));
}

void menuDrawJoin(void) {
    menuDraw(_("Join Game"));

    DrawTextEx(font, _("IP Address"),
               (Vector2){ Ux(0.35f), Uy(0.4f) }, 20, 1, BLACK);
    textBoxDraw(&ipBox);

    DrawTextEx(font, _("Port"),
               (Vector2){ Ux(0.35f), Uy(0.48f) }, 20, 1, BLACK);
    textBoxDraw(&portBox);

    buttonDraw(&backBtn);
    buttonDraw(&startBtn);
}

void menuUpdateJoin(void) {
    textBoxUpdate(&ipBox);
    textBoxUpdate(&portBox);

    if (buttonPressed(&backBtn))
        menuEnter(PLAY);

    if (buttonPressed(&startBtn)) {
        const char *ip = ipBox.buffer[0] ? ipBox.buffer : "127.0.0.1";
        int port = portBox.buffer[0] ? atoi(portBox.buffer) : 2201;

        gameplaySetServer(ip, port);
        screenEnter(GAMEPLAY);
    }
}
