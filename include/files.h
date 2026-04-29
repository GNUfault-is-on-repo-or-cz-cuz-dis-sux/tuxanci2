#ifndef FILES_H
#define FILES_H

#include "raylib.h"

extern Font font;
extern Texture2D bg;
extern Music bgm;

extern Model modelG;
extern Model modelN;
extern Model modelU;
extern Model modelF;
extern Model modelA;
extern Model modelU2;
extern Model modelL;
extern Model modelT;

extern Sound coin;

extern Texture2D x;

void commonLoad(void);
void commonDestroy(void);

#endif // FILES_H