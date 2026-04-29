#include "raylib.h"
#include "screen.h"
#include "intro.h"
#include "mainmenu.h"
#include "menu.h"

GameScreen currentScreen = INTRO;

void screenDraw(void) {
    switch(currentScreen) {
        case INTRO:
            ClearBackground(BLACK);
            drawIntro();
            break;
        case MAINMENU:
            ClearBackground(BLACK);
            drawMainMenu();
            break;
        case MENU:
            ClearBackground(BLACK);
            drawMenu();
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
        case MENU: {
            drawMenu();
            break;
        }
    }
}

void screenUpdate(void) {
    switch (currentScreen) {
        case INTRO: {
            static bool introRan = false;
            if (!introRan) {
                setupIntro();
                enterIntro();
                introRan = true;
            }
            updateIntro();
            break;
        }
        case MAINMENU: {
            static bool mainmenuRan = false;
            if (!mainmenuRan) {
                setupMainMenu();
                enterMainMenu();
                mainmenuRan = true;
            }
            updateMainMenu();
            break;
        }
        case MENU: {
            static bool menuRan = false;
            if(!menuRan) {
                setupMenu();
                enterMenu();
                menuRan = true;
            }
            updateMenu();
            break;
        }
    }
}