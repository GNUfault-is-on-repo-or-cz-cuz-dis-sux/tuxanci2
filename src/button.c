#include "raylib.h"
#include "button.h"
#include "files.h"
#include <stdbool.h>

Button buttonCreate(const char* text, int x, int y, int w, int h) {
    Button b;
    
    b.rect = (Rectangle){
        x,
        y,
        w,
        h
    };
    
    b.text = text;
    b.fontSize = 20;
    
    b.baseColor  = (Color){
        200,
        200,
        200,
        200
    };
    
    b.hoverColor = (Color){
        200,
        200,
        200,
        255
    };
    
    b.hovered = false;
    return b;
}

void buttonDraw(Button* b) {
    DrawRectangleRec(b->rect, b->hovered ? b->hoverColor : b->baseColor);

    int textWidth = MeasureText(b->text, b->fontSize);
    int textX = b->rect.x + (b->rect.width  - textWidth) / 2;
    int textY = b->rect.y + (b->rect.height - b->fontSize) / 2;

    // TODO: Make this not look like a rat's nets
    DrawTextEx(font, b->text, (Vector2){ textX, textY }, b->fontSize, 1.0f, BLACK);
}

bool buttonPressed(Button* b) {
    Vector2 mouse = GetMousePosition();
    b->hovered = CheckCollisionPointRec(mouse, b->rect);

    bool clicked = b->hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    return clicked;
}
