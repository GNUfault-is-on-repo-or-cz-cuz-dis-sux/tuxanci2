#include "window.h"
#include "screen.h"
#include "intro.h"
#include "mainmenu.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

GameScreen currentScreen = INTRO;

void screenDraw(void) {
    switch(currentScreen) {
        case INTRO: {
            static bool introRan = false;
            
            windowClear();

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
            
            windowClear();
            
            if (!mainmenuRan) {
                setupMainmenu();
                enterMainmenu();
                mainmenuRan = true;
            }
            drawMainmenu();
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
            updateMainmenu();
            break;
    }
}
