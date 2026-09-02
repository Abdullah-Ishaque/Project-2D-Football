#include "raylib.h"
#define height 800
#define width 1500


int main(void)
{
    InitWindow( width , height , "Game");
    Texture2D footballField = LoadTexture("resources/Football_field.png");
    SetTargetFPS(60);

    float fieldHeight =  height - 200;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(footballField, 0 , 0, WHITE);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
