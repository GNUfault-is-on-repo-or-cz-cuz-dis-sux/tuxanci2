#include "raylib.h"
#include "music.h"
#include "mainmenu.h"

Texture2D x;

void setupMenu(void) {
    x = LoadTexture("common/images/x.png");
}

void drawMenu(void) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    DrawTexture(bg, 0, 0, WHITE);

    DrawRectangleGradientV(
        0, 0, width, height,
        Fade(BLACK, 0.5f),
        Fade(BLACK, 1.0f)
    );
}

void drawMenu3D(void) {}

void enterMenu(void) {}

void updateMenu(void) {
    musicUpdate();
}

void destroyMenu(void) {}