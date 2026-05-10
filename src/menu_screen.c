#include "raylib.h"
#include "mainmenu.h"
#include "screen.h"
#include "files.h"
#include "menu.h"
#include "menu_screen.h"
#include "play.h"

GameMenu currentMenu = NO_MENU;

void setupMenuScreen(void) {
    menuSetupPlay();
}

void drawMenuScreen(void) {
    int width  = GetScreenWidth();
    int height = GetScreenHeight();

    DrawTexture(bg, 0, 0, WHITE);

    DrawRectangleGradientV(
        0, 0, width, height,
        Fade(BLACK, 0.5f),
        Fade(BLACK, 1.0f)
    );

    switch(currentMenu) {
        case PLAY: {
            menuDrawPlay();
        }
        case NO_MENU: break;
    }
}

void drawMenuScreen3D(void) {}

void enterMenuScreen(void) {}

void updateMenuScreen(void) {
    UpdateMusicStream(bgm);

    switch(currentMenu) {
        case PLAY: {
            menuUpdatePlay();
        }
        case NO_MENU: break;
    }
}
