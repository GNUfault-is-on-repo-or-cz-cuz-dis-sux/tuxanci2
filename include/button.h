#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <stdbool.h>

typedef struct Button {
    Rectangle rect;
    const char* text;
    int fontSize;
    Color baseColor;
    Color hoverColor;
    bool hovered;
} Button;

Button buttonCreate(const char* text, int x, int y, int w, int h);
void buttonDraw(Button* b);
bool buttonPressed(Button* b);

#endif // BUTTON_H