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
 * @brief Story mode
 */

#include "raylib.h"
#include "game/camera.h"
#include "game/files.h"
#include "game/bgm.h"

Vector2 textPosition = (Vector2){5.0f, 0.0f};

Vector3 tuxPosition = { 0.0f, -1.0f, 0.0f };
float tuxSize = 0.1f;

static float timer = 0.0f;

typedef enum  {
    NO_CHAR,
    TUX,
    BAD_TUX,
    NOLOK
} character;

typedef enum message {
    NO_MSG,
    WHY_DO_YOU_HATE_ME
} message;

character currentCharacter = NO_CHAR;
message currentMessage = NO_MSG;

static void switchCharacter(character character) {
    currentCharacter = character;
}

static void switchMessage(message message) {
    currentMessage = message;
}

static void drawTux3D(void) {
    DrawModel(tux, tuxPosition, tuxSize, WHITE);
}

static void drawTux2D(void) {
    DrawTextEx(fontHeader, "Tux", textPosition, 40.0f, 0, WHITE);
}

static void drawBadTux3D(void) {
    DrawModel(tux, tuxPosition, tuxSize, WHITE);
}

static void drawBadTux2D(void) {
    DrawTextEx(fontHeader, "\"Bad\" Tux", textPosition, 40.0f, 0, WHITE);
}

static void drawNolok3D(void) {
    DrawTextEx(fontHeader, "Nolok", textPosition, 40.0f, 0, WHITE);
}

static void drawNolok2D(void) {}

static void drawCharacter3D(void) {
    switch (currentCharacter) {
        case TUX: {
            drawTux3D();
            break;
        }
        case BAD_TUX: {
            drawBadTux3D();
            break;
        }
        case NOLOK: {
            drawNolok3D();
            break;
        }
    }
}

static void drawCharacter2D(void) {
    switch (currentCharacter) {
        case NO_MSG:
            break;
        case TUX: {
            drawTux2D();
            break;
        }
        case BAD_TUX: {
            drawBadTux2D();
            break;
        }
        case NOLOK: {
            drawNolok2D();
            break;
        }
    }
}

static void drawMessageWhyDoYouHateMe(void) {

}

static void drawMessage(void) {
    switch (currentMessage) {
        case NO_MSG:
            break;
        case WHY_DO_YOU_HATE_ME: {
            drawMessageWhyDoYouHateMe();
            break;
        }
    }
}

void setupStory(void) {
    bgmStop();
    DisableCursor();
    cameraMode = CAMERA_CUSTOM;
}

void drawStory(void) {
    ClearBackground((Color){36, 36, 36, 255});

    drawCharacter2D();
    drawMessage();
}

void drawStory3D(void) {
    drawCharacter3D();
}

void updateStory(void) {
    timer += GetFrameTime();

    if (timer <= 1.0f) {
        switchCharacter(TUX);
    } else if (timer <= 2.0f) {
        switchCharacter(BAD_TUX);
    } else {
        switchCharacter(NO_CHAR);
    }    
}
