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
#include "list.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "desc.h"
#include "window.h"

/// @brief Back Button
static Button backBtn;

/// @brief Start Button;
static Button startBtn;

/// @brief Legacy map list
static List mapList;

/// @brief Setup Button, list, and play music (use in screen.c only)
void menuSetupSingleplayer(void) {
    backBtn = buttonCreate(_("Back"), Ux(0.303f), Uy(0.75f), Uy(0.14f), Uy(0.047f));
    startBtn = buttonCreate(_("Start"), Ux(0.618f), Uy(0.75f), Uy(0.14f), Uy(0.047f));

    mapList = listCreate(Ux(0.31f), Uy(0.235f), Uy(0.25f), Uy(0.5f));

/* 
    for (int i = 0; i < t2aMaps.count; i++)
        listAdd(&mapList, t2aMaps.arenas[i].arenaName);

    for (int i = 0; i < legacyMaps.count; i++)
        listAdd(&mapList, legacyMaps.arenas[i].name);
 */  
}

/// @brief Draw Button, map list, and preview image (use in screen.c only)
void menuDrawSingleplayer(void) {
    menuDraw(_("Singleplayer"));
    buttonDraw(&backBtn);
    buttonDraw(&startBtn);
    listDraw(&mapList);

/*    
    int idx = mapList.selectedIndex;
    if (idx >= 0 && idx < (t2aMaps.count + legacyMaps.count)) {
        Texture2D preview;
        const char *description = NULL;
        if (idx < t2aMaps.count) {
            preview = t2aMaps.arenas[idx].arenaImage;
            description = t2aMaps.arenas[idx].arenaDesc;
        } else {
            int legacyIdx = idx - t2aMaps.count;
            preview = legacyMaps.arenas[legacyIdx].screen;
            description = "Legacy arena";
        }

        Rectangle sourceRec = { 0.0f, 0.0f, (float)preview.width, (float)preview.height };
        
        Rectangle destRec = { Ux(0.49f), Uy(0.24f), 320.0f, 240.0f };
        
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(preview, sourceRec, destRec, origin, 0.0f, WHITE);
        
        descDraw(Ux(0.465f), Uy(0.48f), Uy(0.4f), Uy(0.25f), description);
    }
 */
}

/// @brief Update music, list, and Buttons
void menuUpdateSingleplayer(void) {
    listCheck(&mapList);

    if (buttonPressed(&backBtn))
        menuEnter(PLAY);

    if (buttonPressed(&startBtn))
        screenEnter(GAMEPLAY);
}
