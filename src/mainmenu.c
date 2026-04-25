#include "raylib.h"
#include "window.h"

Music bgm;
Texture2D bg;

void setupMainmenu(void) {
    bgm = LoadMusicStream("menu/music/menu.ogg");
    bg = LoadTexture("menu/images/menu.png");
}

void drawMainmenu(void) {
    float scale = (float)GetScreenWidth() / bg.width;
    DrawTextureEx(bg, (Vector2){ 0, 0 }, 0.0f, scale, WHITE);
}

void enterMainmenu(void) {
    PlayMusicStream(bgm);
}

void updateMainmenu(void) {
    UpdateMusicStream(bgm);
}

void destroyMainmenu(void) {
    UnloadMusicStream(bgm);
    UnloadTexture(bg);
}