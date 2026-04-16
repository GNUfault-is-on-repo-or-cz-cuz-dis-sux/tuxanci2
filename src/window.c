#include "window.h"
#include "error.h"

static Font gFont;

void windowInit(int w, int h, int fps, const char* title) {
    InitWindow(w, h, title);
    SetTargetFPS(fps);

    if (FileExists("fonts/font.ttf")) {
        gFont = LoadFont("fonts/font.ttf");
    }
}

void windowDestroy() {
    UnloadFont(gFont);
    CloseWindow();
}

void windowClear(void) {
    ClearBackground(BLACK);
}

void DrawTextCentered(const char *text, int fontSize, Color color) {
    Vector2 size = MeasureTextEx(gFont, text, (float)fontSize, 0);
    int textWidth = (int)size.x;
    int x = (WINDOW_WIDTH - textWidth) / 2;
    int y = (WINDOW_HEIGHT - fontSize) / 2;

    DrawTextEx(gFont, text, (Vector2){ (float)x, (float)y }, (float)fontSize, 0, color);
}
