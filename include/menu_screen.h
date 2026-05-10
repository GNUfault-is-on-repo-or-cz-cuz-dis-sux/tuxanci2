#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include "raylib.h"

typedef enum {
    NO_MENU,
    PLAY
} GameMenu;

extern GameMenu currentMenu;

void setupMenuScreen(void);
void drawMenuScreen(void);
void drawMenuScreen3D(void);
void enterMenuScreen(void);
void updateMenuScreen(void);

#endif // MENU_SCREEN_H