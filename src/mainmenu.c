#include "raylib.h"
#include "window.h"
#include "button.h"

static Button btnQuit;

Music bgm;
Texture2D bg;

static void onQuit(void) {
    CloseWindow();
}

void setupMainmenu(void) {
    bgm = LoadMusicStream("menu/music/menu.ogg");
    bg = LoadTexture("menu/images/menu.png");
    btnQuit = buttonCreate(400, 300, 32, "Quit", onQuit);
}

void drawMainmenu(void) {
    float scale = (float)GetScreenWidth() / bg.width;
    DrawTextureEx(bg, (Vector2){ 0, 0 }, 0.0f, scale, WHITE);
    buttonDraw(&btnQuit);
}

void enterMainmenu(void) {
    PlayMusicStream(bgm);
}

void updateMainmenu(void) {
    UpdateMusicStream(bgm);
    buttonUpdate(&btnQuit);
}

void destroyMainmenu(void) {
    UnloadMusicStream(bgm);
    UnloadTexture(bg);
}