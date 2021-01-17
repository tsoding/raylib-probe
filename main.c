#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60

#define DELTA_TIME (1.0f / SCREEN_FPS)
#define POG_SCALING 1.0f
#define POG_VELOCITY 100.0f

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
               "raylib probe");

    Texture2D pog = LoadTexture("./tsodinPog.png");
    Shader shader = LoadShader(0, TextFormat("./wave.fs", 330));

    int secondsLoc = GetShaderLocation(shader, "secondes");
    int freqXLoc = GetShaderLocation(shader, "freqX");
    int freqYLoc = GetShaderLocation(shader, "freqY");
    int ampXLoc = GetShaderLocation(shader, "ampX");
    int ampYLoc = GetShaderLocation(shader, "ampY");
    int speedXLoc = GetShaderLocation(shader, "speedX");
    int speedYLoc = GetShaderLocation(shader, "speedY");

    // Shader uniform values that can be updated at any time
    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    float screenSize[2] = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(shader, GetShaderLocation(shader, "size"), &screenSize, UNIFORM_VEC2);
    SetShaderValue(shader, freqXLoc, &freqX, UNIFORM_FLOAT);
    SetShaderValue(shader, freqYLoc, &freqY, UNIFORM_FLOAT);
    SetShaderValue(shader, ampXLoc, &ampX, UNIFORM_FLOAT);
    SetShaderValue(shader, ampYLoc, &ampY, UNIFORM_FLOAT);
    SetShaderValue(shader, speedXLoc, &speedX, UNIFORM_FLOAT);
    SetShaderValue(shader, speedYLoc, &speedY, UNIFORM_FLOAT);

    float seconds = 0.0f;

    SetTargetFPS(SCREEN_FPS);

    Vector2 pog_position = {0};
    Vector2 pog_velocity = {
        POG_VELOCITY * DELTA_TIME,
        POG_VELOCITY * DELTA_TIME
    };

    while (!WindowShouldClose()) {
        seconds += GetFrameTime();

        SetShaderValue(shader, secondsLoc, &seconds, UNIFORM_FLOAT);


        if (pog_position.y + pog.height * POG_SCALING > SCREEN_HEIGHT ||
            pog_position.y < 0) {
            pog_velocity.y = -pog_velocity.y;
        }

        if (pog_position.x + pog.width * POG_SCALING > SCREEN_WIDTH ||
            pog_position.x < 0) {
            pog_velocity.x = -pog_velocity.x;
        }

        pog_position = Vector2Add(pog_position, pog_velocity);

        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
            DrawTextureEx(pog, pog_position, 0.0f, POG_SCALING, WHITE);
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
