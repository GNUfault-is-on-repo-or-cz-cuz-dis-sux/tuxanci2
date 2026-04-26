#include "raylib.h"
#include "window.h"
#include "screen.h"
#include "intro.h"
#include "mainmenu.h"

GameScreen currentScreen = INTRO;

void screenDraw(void) {
    switch(currentScreen) {
        case INTRO: {
            static bool introRan = false;
            
            ClearBackground(BLACK);

            if (!introRan) {
                setupIntro();
                enterIntro();
                introRan = true;
            }
            drawIntro();

            break;
        }
        case MAINMENU: {
            static bool mainmenuRan = false;
            
            ClearBackground(BLACK);
            
            if (!mainmenuRan) {
                setupMainMenu();
                enterMainMenu();
                mainmenuRan = true;
            }
            drawMainMenu();
            break;
        }
    }
}

void screenDraw3D(void) {
    switch(currentScreen) {
        case INTRO: {
            drawIntro3D();
            break;
        }
        case MAINMENU: {
            drawMainMenu3D();
            break;
        }
    }
}

void screenUpdate(void) {
    switch (currentScreen) {
        case INTRO:
            updateIntro();
            break;

        case MAINMENU:
            updateMainMenu();
            break;
    }
}
