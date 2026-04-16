#include <stdio.h>
#include <unistd.h>
#include "window.h"
#include "error.h"
#include "screen.h"
#include "intro.h"

void cleanup(void) {
    windowDestroy();
    destroyIntro();
}

int main(void) {
    // temporary fix
    chdir("data");
    
    windowInit(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FPS, WINDOW_TITLE);

    InitAudioDevice();

    // Main loop
    while(!WindowShouldClose()) {
        screenUpdate();
        
        BeginDrawing();
            windowClear();
            screenDraw();
        EndDrawing();
    }

    cleanup();

    return 0;
}