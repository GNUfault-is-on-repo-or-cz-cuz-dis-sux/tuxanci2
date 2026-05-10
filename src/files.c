#include "raylib.h"
#include "screen.h"

Texture2D bg;
Font font;
Music bgm;
Texture2D explosions;

void commonLoad(void) {
    bg         = LoadTexture("common/images/main.jpg");
    font       = LoadFont("common/fonts/font.ttf");
    bgm        = LoadMusicStream("common/music/menu.ogg");
    explosions = LoadTexture("menu/images/explosions.jpg");

}

void commonDestroy(void) {
    UnloadTexture(bg);
    UnloadFont(font);
    UnloadMusicStream(bgm);
    UnloadTexture(explosions);
}