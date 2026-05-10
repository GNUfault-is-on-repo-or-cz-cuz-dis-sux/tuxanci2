#ifndef FILES_H
#define FILES_H

#include "raylib.h"

extern Texture2D bg;
extern Font font;
extern Music bgm;
extern Texture2D explosions;

void commonLoad(void);
void commonDestroy(void);

#endif // FILES_H