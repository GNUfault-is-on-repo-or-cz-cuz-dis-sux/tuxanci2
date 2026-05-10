#include "raylib.h"
#include "button.h"
#include "screen.h"
#include "files.h"
#include "menu.h"

static Button backBtn;

void menuSetupPlay(void) {
    backBtn = buttonCreate("Back", 140, 650, 150, 50);
    PlayMusicStream(bgm);
}

void menuDrawPlay(void) {
    menuDraw("Play");
    buttonDraw(&backBtn);
}

void menuUpdatePlay(void) {
    UpdateMusicStream(bgm);

    if(buttonPressed(&backBtn)) {
        currentMenu = NO_MENU;
        currentScreen = MAINMENU;
    }
}
