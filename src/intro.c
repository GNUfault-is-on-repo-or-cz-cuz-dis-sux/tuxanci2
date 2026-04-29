/*
 * TODO:
 * I need to add back the boom sound when the letters drop.
 * I removed them as they used up a ton of memory.
 * Add them back before first alpha.
 */

#include "raylib.h"
#include "raymath.h"
#include "screen.h"
#include "files.h"
#include "camera.h"

static int framesCounter = 0;
static int state = 0;
static float alpha = 1.0f;

static float spinTimer = 0.0f;
static float spinAlpha = 1.0f;
#define SPIN_DURATION 5.0f
#define NUM_LETTERS 8
#define DROP_INTERVAL 0.25f
#define LAND_Y 0.0f

#define MAX_PARTICLES 1000
#define SHAKE_DURATION 0.5f
#define SHAKE_MAGNITUDE 1.0f

#define LOGO_HOLD_DURATION 0.5f

typedef struct {
    Vector3 pos;
    Vector3 vel;
    float life;
    float maxLife;
} DustParticle;

static float letterY[NUM_LETTERS];
static bool letterLanded[NUM_LETTERS];
static bool letterDropped[NUM_LETTERS];

static DustParticle particles[NUM_LETTERS][MAX_PARTICLES];
static float shakeTimer[NUM_LETTERS];
static Vector2 shakeOffset;

static float logoHoldTimer = 0.0f;

void setupIntro(void) {
    camera.position = (Vector3){
        0.0f,
        4.0f, 
        20.0f
    };
   
    camera.target = (Vector3){
        0.0f,
        0.0f,
        0.0f
    };
    
    camera.up = (Vector3){
        0.0f,
        1.0f,
        0.0f
    };
    
    camera.fovy = 25.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void enterIntro(void) {
    framesCounter = 0;
    state = 0;
    alpha = 1.0f;
    spinTimer = 0.0f;
    spinAlpha = 1.0f;
    logoHoldTimer = 0.0f;
    
    shakeOffset = (Vector2){
        0.0f,
        0.0f
    };

    PlaySound(coin);

    for (int i = 0; i < NUM_LETTERS; i++) {
        letterY[i] = 8.0f;
        letterLanded[i] = false;
        letterDropped[i] = false;
        shakeTimer[i] = 0.0f;
        for (int p = 0; p < MAX_PARTICLES; p++) {
            particles[i][p].life = 0.0f;
        }
    }
}

static void spawnDust(int idx, float worldX) {
    for (int p = 0; p < MAX_PARTICLES; p++) {
        DustParticle *dp = &particles[idx][p];
        dp->pos = (Vector3){
            worldX + ((float)GetRandomValue(-120, 120) / 100.0f),
            LAND_Y + ((float)GetRandomValue(0, 15) / 100.0f),
            ((float)GetRandomValue(-30, 30) / 100.0f)
        };
        dp->vel = (Vector3){
            ((float)GetRandomValue(-200, 200) / 100.0f) * 1.8f,
            ((float)GetRandomValue(30, 300) / 100.0f) * 1.4f,
            ((float)GetRandomValue(-80, 80) / 100.0f) * 0.5f
        };
        dp->maxLife = (float)GetRandomValue(35, 100) / 100.0f;
        dp->life = dp->maxLife;
    }
}

void updateIntro(void) {
    float dt = GetFrameTime();

    if (GetKeyPressed() != 0) {
        currentScreen = MAINMENU;
        return;
    }

    if (state == 0) {
        logoHoldTimer += dt;
        if (logoHoldTimer >= LOGO_HOLD_DURATION) {
            alpha -= dt * 3.0f;
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                state = 1;
            }
        }
    }
    else if (state == 1) {
        spinTimer += dt;

        Model *letters[NUM_LETTERS] = {
            &modelG, &modelN, &modelU, &modelF,
            &modelA, &modelU2, &modelL, &modelT
        };

        BoundingBox bb0 = GetModelBoundingBox(*letters[0]);
        float letterWidth = bb0.max.x - bb0.min.x;
        float spacing = letterWidth * 1.1f;
        float totalWidth = (NUM_LETTERS - 1) * spacing;
        float startX = -totalWidth / 2.0f;

        shakeOffset = (Vector2){
            0.0f,
            0.0f
        };

        for (int i = 0; i < NUM_LETTERS; i++) {
            if (!letterDropped[i] && spinTimer >= i * DROP_INTERVAL) {
                letterDropped[i] = true;
                letterY[i] = 8.0f;
            }

            if (letterDropped[i] && !letterLanded[i]) {
                letterY[i] -= 20.0f * dt;
                if (letterY[i] <= LAND_Y) {
                    letterY[i] = LAND_Y;
                    letterLanded[i] = true;

                    shakeTimer[i] = SHAKE_DURATION;

                    BoundingBox lbb = GetModelBoundingBox(*letters[i]);
                    float cx = (lbb.min.x + lbb.max.x) / 2.0f;
                    float wx = startX + i * spacing - cx;
                    spawnDust(i, wx);
                }
            }

            if (shakeTimer[i] > 0.0f) {
                shakeTimer[i] -= dt;
                float t = shakeTimer[i] / SHAKE_DURATION;
                float mag = t * t * SHAKE_MAGNITUDE;
                shakeOffset.x += ((float)GetRandomValue(-100, 100) / 100.0f) * mag;
                shakeOffset.y += ((float)GetRandomValue(-100, 100) / 100.0f) * mag;
            }

            for (int p = 0; p < MAX_PARTICLES; p++) {
                DustParticle *dp = &particles[i][p];
                if (dp->life <= 0.0f) continue;
                dp->life -= dt;
                dp->pos.x += dp->vel.x * dt;
                dp->pos.y += dp->vel.y * dt;
                dp->pos.z += dp->vel.z * dt;
                dp->vel.y -= 3.5f * dt;
                dp->vel.x *= 0.97f;
                dp->vel.z *= 0.97f;
            }
        }

        if (spinTimer >= SPIN_DURATION - 1.0f) {
            spinAlpha -= dt;
            if (spinAlpha < 0.0f) spinAlpha = 0.0f;
        }

        if (spinTimer >= SPIN_DURATION) {
            currentScreen = MAINMENU;
        }
    }
}

void drawIntro(void) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    if (state == 0) {
        ClearBackground(RAYWHITE);

        Color c = Fade(BLACK, alpha);

        DrawRectangle(width / 2 - 128, height / 2 - 128, 256, 16, c);
        DrawRectangle(width / 2 - 128, height / 2 - 128, 16, 256, c);
        DrawRectangle(width / 2 + 112, height / 2 - 128, 16, 256, c);
        DrawRectangle(width / 2 - 128, height / 2 + 112, 256, 16, c);

        DrawText("raylib", width / 2 - 44, height / 2 + 48, 50, c);

        int poweredWidth = MeasureText("powered", 30);
        DrawText("powered", width / 2 - poweredWidth / 2, height / 2 + 160, 30, c);
    }
    else if (state == 1) {
        ClearBackground(BLACK);
    }
}

void drawIntro3D(void) {
    if (state != 1) return;

    Model *letters[NUM_LETTERS] = {
        &modelG, &modelN, &modelU, &modelF,
        &modelA, &modelU2, &modelL, &modelT
    };

    BoundingBox bb = GetModelBoundingBox(*letters[0]);
    float letterWidth = bb.max.x - bb.min.x;
    float spacing = letterWidth * 1.1f;
    float totalWidth = (NUM_LETTERS - 1) * spacing;
    float startX = -totalWidth / 2.0f;

    Color tint = Fade(WHITE, spinAlpha);

    camera.position = (Vector3){
        0.0f + shakeOffset.x,
        4.0f + shakeOffset.y,
        20.0f
    };

    for (int i = 0; i < NUM_LETTERS; i++) {
        if (!letterDropped[i]) continue;

        BoundingBox lbb = GetModelBoundingBox(*letters[i]);
        float cx = (lbb.min.x + lbb.max.x) / 2.0f;
        float cy = lbb.min.y;

        float px = startX + i * spacing - cx;
        float py = letterY[i] - cy;

        letters[i]->transform = MatrixIdentity();
        DrawModel(*letters[i], (Vector3){ px, py, 0.0f }, 1.0f, tint);

        for (int p = 0; p < MAX_PARTICLES; p++) {
            DustParticle *dp = &particles[i][p];
            if (dp->life <= 0.0f) continue;
            float t = dp->life / dp->maxLife;
            unsigned char a = (unsigned char)(t * 255.0f * spinAlpha);
            
            Color dustColor = (Color){
                255,
                255,
                255,
                a
            };
            
            DrawPoint3D(dp->pos, dustColor);
        }
    }
}
