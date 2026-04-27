#ifndef MUSIC_H
#define MUSIC_H

#include "raylib.h"

extern Music music;

void musicLoad(void);
void musicPlay(void);
void musicUpdate(void);
void musicDestroy(void);

#endif // MUSIC_H