#ifndef SCREEN_H
#define SCREEN_H

typedef enum {
    INTRO,
    MAINMENU
} GameScreen;

extern GameScreen currentScreen;

void screenUpdate(void);
void screenDraw(void);

#endif // SCREEN_H
