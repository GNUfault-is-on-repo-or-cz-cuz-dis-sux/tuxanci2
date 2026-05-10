#include "raylib.h"
#include "button.h"
#include "files.h"
#include "menu.h"
#include "screen.h"

static Button playBtn;
static Button quitBtn;

void setupMainMenu(void) {
    playBtn = buttonCreate("Play", 200, 300, 150, 50);
    quitBtn = buttonCreate("Quit", 200, 360, 150, 50);
}

void drawMainMenu(void) {
    float scale = (float)GetScreenWidth() / bg.width;
    DrawTextureEx(bg, (Vector2){ 0, 0 }, 0.0f, scale, WHITE);

    buttonDraw(&playBtn);
    buttonDraw(&quitBtn);
}

void drawMainMenu3D(void) {}

void enterMainMenu(void) {
    PlayMusicStream(bgm);
}

void updateMainMenu(void) {
    UpdateMusicStream(bgm);

    if (buttonPressed(&playBtn)) {
        currentMenu = PLAY;
    }

    if (buttonPressed(&quitBtn)) {
        // FIXME: This just does a segfault for some reason, prob a memory leak or whatever
        CloseWindow();
    }
}
