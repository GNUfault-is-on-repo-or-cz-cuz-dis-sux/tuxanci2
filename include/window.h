#ifndef WINDOW_H
#define WINDOW_H

#include "raylib.h"

#define WINDOW_WIDTH          800
#define WINDOW_HEIGHT         600
#define WINDOW_FPS            60
#define WINDOW_TITLE          "Tuxanci 2"

void windowInit(int w, int h, int fps, const char* title);
void windowDestroy(void);
void windowClear(void);
void DrawTextCentered(const char *text, int fontSize, Color color);

#endif // WINDOW_H