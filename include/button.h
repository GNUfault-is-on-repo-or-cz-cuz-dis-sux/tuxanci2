#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <stdbool.h>

typedef void (*ButtonCallback)(void);

typedef struct {
    float x, y;
    float fontSize;
    const char *label;
    ButtonCallback onClick;
    bool enabled;
    float hoverT;
} Button;

Button buttonCreate(float x, float y, float fontSize, const char *label, ButtonCallback onClick);

void buttonDraw(const Button *btn);
bool buttonUpdate(Button *btn);
bool buttonTick(Button *btn);

#endif // BUTTON_H