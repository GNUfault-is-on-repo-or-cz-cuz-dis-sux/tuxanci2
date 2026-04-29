#include "button.h"
#include "raylib.h"
#include "files.h"
#include <stdbool.h>

static const Color BTN_WHITE = {
    255,
    255,
    255,
    255
};

static const Color BTN_YELLOW = {
    255,
    220,
    50,
    255
};

static const Color BTN_SHADOW = {
    0,
    0,
    0,
    160
};

static Color lerpColor(Color a, Color b, float t) {
    return (Color){
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t),
    };
}

static Rectangle textBounds(const Button *btn) {
    Vector2 size = MeasureTextEx(font, btn->label, btn->fontSize, 0);
    return (Rectangle){
        btn->x,
        btn->y,
        size.x,
        size.y
    };
}

Button buttonCreate(float x, float y, float fontSize, const char *label, ButtonCallback onClick) {
    return (Button){
        .x = x,
        .y = y,
        .fontSize = fontSize,
        .label = label,
        .onClick = onClick,
        .enabled = true,
        .hoverT = 0.0f,
    };
}

void buttonDraw(const Button *btn) {
    Color color = lerpColor(BTN_WHITE, BTN_YELLOW, btn->hoverT);

    Vector2 shadowPos = {
        btn->x + 2,
        btn->y + 2
    };

    DrawTextEx(font, btn->label, shadowPos, btn->fontSize, 0, BTN_SHADOW);

    Vector2 pos = {
        btn->x,
        btn->y
    };

    DrawTextEx(font, btn->label, pos, btn->fontSize, 0, color);
}

bool buttonUpdate(Button *btn) {
    if (!btn->enabled) return false;

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, textBounds(btn));
    float dt = GetFrameTime();

    float target = hovered ? 1.0f : 0.0f;
    btn->hoverT += (target - btn->hoverT) * 30.0f * dt;
    if (btn->hoverT < 0.001f) btn->hoverT = 0.0f;
    if (btn->hoverT > 0.999f) btn->hoverT = 1.0f;

    bool clicked = hovered && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    if (clicked && btn->onClick) btn->onClick();
    return clicked;
}

bool buttonTick(Button *btn) {
    buttonDraw(btn);
    return buttonUpdate(btn);
}