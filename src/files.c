#include "raylib.h"
#include "screen.h"

Font font;
Texture2D bg;
Music bgm;

// Mainly used in intro.c
Model modelG;
Model modelN;
Model modelU;
Model modelF;
Model modelA;
Model modelU2;
Model modelL;
Model modelT;

// Mainly used in intro.c
Sound coin;

Texture2D x;

void commonLoad(void) {
    font = LoadFont("common/fonts/font.ttf");
    bg = LoadTexture("common/images/main.jpg");
    bgm = LoadMusicStream("common/music/menu.ogg");
    
    // Used in intro.c
    modelG = LoadModel("intro/models/gnufault-letters/G.glb");
    modelN = LoadModel("intro/models/gnufault-letters/N.glb");
    modelU = LoadModel("intro/models/gnufault-letters/U.glb");
    modelF = LoadModel("intro/models/gnufault-letters/F.glb");
    modelA = LoadModel("intro/models/gnufault-letters/A.glb");
    modelU2 = modelU; // TODO: Find a better way to do this
    modelL = LoadModel("intro/models/gnufault-letters/L.glb");
    modelT = LoadModel("intro/models/gnufault-letters/T.glb");
    
    // Also used in intro.c
    coin = LoadSound("intro/sounds/coin.ogg");

    x = LoadTexture("common/images/x.gif");
}

void commonDestroy(void) {
    UnloadFont(font);
    UnloadTexture(bg);
    UnloadMusicStream(bgm);

    /*
     * Do not unload U2, trust me.
     * Used in intro.c
     */
    UnloadModel(modelG);
    UnloadModel(modelN);
    UnloadModel(modelU);
    UnloadModel(modelF);
    UnloadModel(modelA);
    UnloadModel(modelL);
    UnloadModel(modelT);
    
    // Also used in intro.c
    UnloadSound(coin);

    UnloadTexture(x);
}