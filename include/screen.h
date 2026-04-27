#ifndef SCREEN_H
#define SCREEN_H

typedef enum {
    INTRO,
    MAINMENU,
    MENU
} GameScreen;

extern GameScreen currentScreen;

void screenUpdate(void);
void screenDraw(void);
void screenDraw3D(void);

#endif // SCREEN_H
