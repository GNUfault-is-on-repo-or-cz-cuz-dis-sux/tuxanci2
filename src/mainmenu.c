#include "raylib.h"
#include "window.h"
#include "button.h"
#include "screen.h"
#include "files.h"

static Button btnPlay;
static Button btnQuit;

static void onPlay(void) {
    currentScreen = MENU;
}

static void onQuit(void) {
    CloseWindow();
}

void setupMainMenu(void) {
    btnPlay = buttonCreate(250, 300, 32, "Play", onPlay);
    btnQuit = buttonCreate(250, 340, 32, "Quit", onQuit);
}

void drawMainMenu(void) {
    float scale = (float)GetScreenWidth() / bg.width;
    DrawTextureEx(bg, (Vector2){ 0, 0 }, 0.0f, scale, WHITE);
    buttonDraw(&btnPlay);
    buttonDraw(&btnQuit);
}

void drawMainMenu3D(void) {}

void enterMainMenu(void) {
    PlayMusicStream(bgm);
}

void updateMainMenu(void) {
    UpdateMusicStream(bgm);
    buttonUpdate(&btnPlay);
    buttonUpdate(&btnQuit);
}
