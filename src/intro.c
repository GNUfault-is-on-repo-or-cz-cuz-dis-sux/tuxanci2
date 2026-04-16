#include "window.h"
#include "screen.h"

Sound noise;
double introStartTime = 0;

void setupIntro(void) {
    noise = LoadSound("intro/sounds/noise.wav");
}

void enterIntro(void) {
    PlaySound(noise);
    introStartTime = GetTime();
}

void drawIntro(void) {
    DrawTextCentered("GNUfault", 40, WHITE);
}

void updateIntro(void) {
    if (GetTime() - introStartTime >= 2.0) {
        currentScreen = MAINMENU;
    }
}

void destroyIntro(void) {
    UnloadSound(noise);
}
