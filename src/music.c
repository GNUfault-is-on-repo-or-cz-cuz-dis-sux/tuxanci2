#include "raylib.h"

Music music;

void musicLoad(void) {
    music = LoadMusicStream("common/music/menu.ogg");
}

/*
 * I might implement somthing where 
 * I can start and stop the music
 * in the same spot.
 */
void musicPlay(void) {
    PlayMusicStream(music);
}

void musicUpdate(void) {
    UpdateMusicStream(music);
}

void musicDestroy(void) {
    UnloadMusicStream(music);
}