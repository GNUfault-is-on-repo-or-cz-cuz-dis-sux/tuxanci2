#include "window.h"
#include "screen.h"

Music noise;
double introStartTime = 0;

void setupIntro(void) {
    noise = LoadMusicStream("intro/sounds/noise.ogg");
}

void enterIntro(void) {
    PlayMusicStream(noise);
    introStartTime = GetTime();
}

void drawIntro(void) {
    DrawTextCentered("GNUfault", 40, WHITE);
}

void updateIntro(void) {
    UpdateMusicStream(noise);
    
    if (GetTime() - introStartTime >= GetMusicTimeLength(noise)) {
        currentScreen = MAINMENU;
    }
}

void destroyIntro(void) {
    UnloadMusicStream(noise);
}
