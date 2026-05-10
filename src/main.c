#include "raylib.h"
#include "error.h"
#include "screen.h"
#include "files.h"
#include "camera.h"
#include "menu.h"

#define WINDOW_WIDTH          1024
#define WINDOW_HEIGHT         768
#define WINDOW_FPS            60
#define WINDOW_TITLE          "Tuxanci 2"

int main(void) {
    // temporary fix
    ChangeDirectory("data");
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(WINDOW_FPS);

    SetAudioStreamBufferSizeDefault(8192);
    InitAudioDevice();

    commonLoad();

    // Main loop
    while(!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_CUSTOM);
        screenUpdate();
        menuUpdate();
        
        BeginDrawing();
            ClearBackground(BLACK);
            screenDraw();
                screenDraw3D();
            EndMode3D();
        EndDrawing();
    }

    commonDestroy();
    CloseWindow();

    return 0;
}