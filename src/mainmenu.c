#include "raylib.h"
#include "window.h"
#include "button.h"
#include "screen.h"
#include "music.h"

static Button btnPlay;
static Button btnQuit;

Music bgm;
Texture2D bg;

static void onPlay(void) {
    currentScreen = MENU;
}

static void onQuit(void) {
    CloseWindow();
}

void setupMainMenu(void) {
    musicLoad();
    bg = LoadTexture("common/images/main.png");
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
    musicPlay();
}

void updateMainMenu(void) {
    musicUpdate();
    buttonUpdate(&btnPlay);
    buttonUpdate(&btnQuit);
}

void destroyMainMenu(void) {
    musicDestroy();
    UnloadTexture(bg);
}