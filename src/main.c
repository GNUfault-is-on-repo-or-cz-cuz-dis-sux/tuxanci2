#include "raylib.h"
#include "window.h"
#include "error.h"
#include "screen.h"
#include "intro.h"

#define WINDOW_WIDTH          1024
#define WINDOW_HEIGHT         768
#define WINDOW_FPS            60
#define WINDOW_TITLE          "Tuxanci 2"

Font gFont;

int main(void) {
    // temporary fix
    ChangeDirectory("data");
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(WINDOW_FPS);

    if (FileExists("common/fonts/font.ttf")) {
        gFont = LoadFont("common/fonts/font.ttf");
    } else {
        TraceLog(LOG_ERROR, "common/fonts/font.ttf not found!\n");
        return 1;
    }

    SetAudioStreamBufferSizeDefault(8192);
    InitAudioDevice();

    // Main loop
    while(!WindowShouldClose()) {
        screenUpdate();
        
        BeginDrawing();
            ClearBackground(BLACK);
            screenDraw();
        EndDrawing();
    }

    UnloadFont(gFont);
    CloseWindow();
    destroyIntro();

    return 0;
}