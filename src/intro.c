#include "raylib.h"
#include "window.h"
#include "screen.h"

static int framesCounter = 0;
static int lettersCount = 0;

static int topSideRecWidth = 16;
static int leftSideRecHeight = 16;
static int bottomSideRecWidth = 16;
static int rightSideRecHeight = 16;

static int state = 0;
static float alpha = 1.0f;
static float poweredAlpha = 1.0f;

void setupIntro(void) {}

void enterIntro(void) {
    framesCounter = 0;
    lettersCount = 0;
    topSideRecWidth = 16;
    leftSideRecHeight = 16;
    bottomSideRecWidth = 16;
    rightSideRecHeight = 16;
    state = 0;
    alpha = 1.0f;
    poweredAlpha = 1.0f;
}

void updateIntro(void) {
    if (GetKeyPressed() != 0) {
        currentScreen = MAINMENU;
        return;
    }

    if (state == 0) {
        framesCounter++;
        if (framesCounter == 120) {
            state = 1;
            framesCounter = 0;
        }
    }
    else if (state == 1) {
        topSideRecWidth += 4;
        leftSideRecHeight += 4;
        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2) {
        bottomSideRecWidth += 4;
        rightSideRecHeight += 4;
        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3) {
        framesCounter++;
        if (framesCounter / 12) {
            lettersCount++;
            framesCounter = 0;
        }

        if (lettersCount >= 10) {
            alpha -= 0.02f;
            poweredAlpha -= 0.02f;
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                poweredAlpha = 0.0f;
                state = 4;
            }
        }
    }
    else if (state == 4) {
        currentScreen = MAINMENU;
    }
}

void drawIntro(void) {
    int width  = GetScreenWidth();
    int height = GetScreenHeight();

    int logoPositionX = width  / 2 - 128;
    int logoPositionY = height / 2 - 128;

    ClearBackground(RAYWHITE);

    if (state == 0) {
        if ((framesCounter / 15) % 2)
            DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1) {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2) {
        DrawRectangle(logoPositionX,       logoPositionY,       topSideRecWidth,    16, BLACK);
        DrawRectangle(logoPositionX,       logoPositionY,       16, leftSideRecHeight,   BLACK);
        DrawRectangle(logoPositionX + 240, logoPositionY,       16, rightSideRecHeight,  BLACK);
        DrawRectangle(logoPositionX,       logoPositionY + 240, bottomSideRecWidth,  16, BLACK);
    }
    else if (state == 3) {
        DrawRectangle(logoPositionX,       logoPositionY,       topSideRecWidth,          16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX,       logoPositionY + 16,  16, leftSideRecHeight  - 32,  Fade(BLACK, alpha));
        DrawRectangle(logoPositionX + 240, logoPositionY + 16,  16, rightSideRecHeight - 32,  Fade(BLACK, alpha));
        DrawRectangle(logoPositionX,       logoPositionY + 240, bottomSideRecWidth,       16, Fade(BLACK, alpha));

        DrawRectangle(width / 2 - 112, height / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(TextSubtext("raylib", 0, lettersCount),
                 width / 2 - 44, height / 2 + 48, 50, Fade(BLACK, alpha));

        if (lettersCount >= 6) {
            int poweredWidth = MeasureText("powered", 30);
            DrawText("powered", width / 2 - poweredWidth / 2, height / 2 + 160, 30, Fade(BLACK, poweredAlpha));
        }
    }
}

void destroyIntro(void) {}