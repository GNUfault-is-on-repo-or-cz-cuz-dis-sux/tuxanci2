#include "raylib.h"
#include "screen.h"
#include "menu_screen.h"
#include "files.h"

void menuUpdate(void) {
    if(currentMenu != NO_MENU) {
        currentScreen = MENU;
    }
}

void menuDraw(const char* title) {
    int screenWidth  = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    int rectWidth  = 800;
    int rectHeight = 600;
    
    Color color = WHITE;

    int posX = (screenWidth  - rectWidth)  / 2;
    int posY = (screenHeight - rectHeight) / 2;
    
    int size = 40;
    int spacing = 5;

    DrawRectangle(posX, posY, rectWidth, rectHeight + size, color);

    DrawTexture(explosions, posX, posY - size - spacing, WHITE);

    Vector2 pos = (Vector2){
        posX + spacing,
        posY - size - spacing
    };

    DrawTextEx(font, title, pos, size, 0, color);
}
