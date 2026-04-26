#include "raylib.h"
#include "window.h"
#include "button.h"

static Button btnQuit;

Music bgm;
Texture2D bg;

static void onQuit(void) {
    CloseWindow();
}

void setupMainMenu(void) {
    bgm = LoadMusicStream("menu/music/menu.ogg");
    bg = LoadTexture("menu/images/menu.png");
    btnQuit = buttonCreate(400, 300, 32, "Quit", onQuit);
}

void drawMainMenu(void) {
    float scale = (float)GetScreenWidth() / bg.width;
    DrawTextureEx(bg, (Vector2){ 0, 0 }, 0.0f, scale, WHITE);
    buttonDraw(&btnQuit);
}

void drawMainMenu3D(void) {}

void enterMainMenu(void) {
    PlayMusicStream(bgm);
}

void updateMainMenu(void) {
    UpdateMusicStream(bgm);
    buttonUpdate(&btnQuit);
}

void destroyMainMenu(void) {
    UnloadMusicStream(bgm);
    UnloadTexture(bg);
}