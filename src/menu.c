#include "raylib.h"
#include "music.h"
#include "mainmenu.h"
#include "screen.h"

Texture2D x;

static float xHoverT = 0.0f;

#define X_BTN_MARGIN 16
#define X_BTN_Y 16

void setupMenu(void) {
    x = LoadTexture("common/images/x.gif");
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

    int btnX = GetScreenWidth() - x.width - X_BTN_MARGIN;
    Color tint = (Color){
        255,
        (unsigned char)(255 - (int)(xHoverT * 80)),
        (unsigned char)(255 - (int)(xHoverT * 80)),
        255
    };
    DrawTexture(x, btnX, X_BTN_Y, tint);
}

void drawMenu3D(void) {}

void enterMenu(void) {
    xHoverT = 0.0f;
}

void updateMenu(void) {
    musicUpdate();

    int btnX = GetScreenWidth() - x.width - X_BTN_MARGIN;
    Rectangle xRect = {
        (float)btnX,
        X_BTN_Y,
        (float)x.width,
        (float)x.height
    };

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, xRect);
    float dt = GetFrameTime();

    float target = hovered ? 1.0f : 0.0f;
    xHoverT += (target - xHoverT) * 30.0f * dt;
    if (xHoverT < 0.001f) xHoverT = 0.0f;
    if (xHoverT > 0.999f) xHoverT = 1.0f;

    if (hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        currentScreen = MAINMENU;
    }
}

void destroyMenu(void) {
    UnloadTexture(x);
}