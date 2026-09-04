#include <stdio.h>
#include "raylib.h"
#define height 800
#define width 1500

int main(void)
{
    InitWindow(width, height, "Game");
    Texture2D football_Field = LoadTexture("resources/Football_field.png");
    Texture2D intro = LoadTexture("resources/Start1.png");
    Texture2D option = LoadTexture("resources/Option.png");

    int starting_click = 0;
    int option_click = 0;
    float radius = 40;
    float positionB1X = 90.2;
    float positionB1Y = 405.75;

    float positionB2X = 289.15;
    float positionB2Y = 255.75;

    float positionB3X = 289.15;
    float positionB3Y = 555.75;

    float positionB4X = 438.1;
    float positionB4Y = 405.75;

    float positionB5X = 587.05;
    float positionB5Y = 255.75;

    float positionB6X = 587.05;
    float positionB6Y = 555.75;

    float positionR1X = 1409.8;
    float positionR1Y = 405.75;

    float positionR2X = 1210.85;
    float positionR2Y = 255.75;

    float positionR3X = 1210.85;
    float positionR3Y = 555.75;

    float positionR4X = 1062;
    float positionR4Y = 405.75;

    float positionR5X = 913;
    float positionR5Y = 255.75;

    float positionR6X = 913;
    float positionR6Y = 555.75;

    SetTargetFPS(60);

    float fieldHeight = height - 200;
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!starting_click)
        {
            DrawTexture(intro, 0, 0, WHITE);
            starting_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        }
        // if (starting_click && !option_click)
        // {
        //     Rectangle background = {0, 0, 1500, 800};
        //     DrawRectangleRec(background, GREEN);
        //     DrawTexture(option, 450, 250, WHITE);
        // }
        // if ((GetMouseX() >= 450 && GetMouseX() <= 1050) && (GetMouseY() >= 250 && GetMouseY() <= 550) && !option_click)
        // {
        //     option_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        // }
        // printf("%d" , option_click);
        // printf("%d\n" , GetMouseX());
        if (starting_click)
        {
            DrawTexture(football_Field, 0, 0, WHITE);
            DrawText("Football 2D", 650, 50, 50, BLUE);
            DrawCircle(positionB1X, positionB1Y, radius, BLUE);
            DrawCircle(positionB2X, positionB2Y, radius, BLUE);
            DrawCircle(positionB3X, positionB3Y, radius, BLUE);
            DrawCircle(positionB4X, positionB4Y, radius, BLUE);
            DrawCircle(positionB5X, positionB5Y, radius, BLUE);
            DrawCircle(positionB6X, positionB6Y, radius, BLUE);
            DrawCircle(positionR1X, positionR1Y, radius, RED);
            DrawCircle(positionR2X, positionR2Y, radius, RED);
            DrawCircle(positionR3X, positionR3Y, radius, RED);
            DrawCircle(positionR4X, positionR4Y, radius, RED);
            DrawCircle(positionR5X, positionR5Y, radius, RED);
            DrawCircle(positionR6X, positionR6Y, radius, RED);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
