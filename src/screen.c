#include "raylib.h"
#include "screen.h"
#include "mainmenu.h"
#include "menu_screen.h"

GameScreen currentScreen = MAINMENU;

void screenDraw(void) {
    switch(currentScreen) {
        case MAINMENU:
            ClearBackground(BLACK);
            drawMainMenu();
            break;
        case MENU:
            ClearBackground(BLACK);
            drawMenuScreen();
    }
}

void screenDraw3D(void) {
    switch(currentScreen) {
        case MAINMENU: {
            drawMainMenu3D();
            break;
        }
        case MENU: {
            drawMenuScreen();
            break;
        }
    }
}

void screenUpdate(void) {
    switch (currentScreen) {
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
                setupMenuScreen();
                enterMenuScreen();
                menuRan = true;
            }
            updateMenuScreen();
            break;
        }
    }
}