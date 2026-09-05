#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#define height 800
#define width 1500
#define border1X = 50.2;
#define border2X = 1450.4;
#define border1Y = 120;
#define border2Y = 680;

int main(void)
{
    InitWindow(width, height, "Game");
    Texture2D football_Field = LoadTexture("resources/Football_field.png");
    Texture2D intro = LoadTexture("resources/Start1.png");
    Texture2D option = LoadTexture("resources/Option.png");

    int starting_click = 0;
    int option_click = 0;
    float radius = 40;

    Vector2 positionB1 = {90.2, 405.75};

    Vector2 positionB2 = {289.15, 255.75};

    Vector2 positionB3 = {289.15, 555.75};

    Vector2 positionB4 = {438.1, 405.75};

    Vector2 positionB5 = {587.05, 255.75};

    Vector2 positionB6 = {587.05, 555.75};

    Vector2 positionR1 = {1409.8, 405.75};

    Vector2 positionR2 = {1210.85, 255.75};

    Vector2 positionR3 = {1210.85, 555.75};

    Vector2 positionR4 = {1062, 405.75};

    Vector2 positionR5 = {913, 255.75};

    Vector2 positionR6 = {913, 555.75};

    Vector2 player_speed[12] = {0};

    Vector2 launch_direction = Vector2Zero();

    bool is_dragging = false;
    Vector2 dragged = Vector2Zero();
    float power = 0.0;
    float max_power = 700.0;
    float max_speed = 400.0;
    float power_speed = 7;
    Vector2 anchor_point = Vector2Zero();
    int push[12] = {0};
    Vector2 *positions[12] = {&positionB1, &positionB2, &positionB3, &positionB4, &positionB5, &positionB6, &positionR1,&positionR2,&positionR3,&positionR4,&positionR5,&positionR6};

    // CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);

    SetTargetFPS(60);

    float fieldHeight = height - 200;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mouse_position = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (int i = 0; i < 12; i++)
            {
                if (CheckCollisionPointCircle(mouse_position, *positions[i], radius))
                {
                    is_dragging = true;
                    anchor_point = *positions[i];
                    player_speed[i] = Vector2Zero();
                    for (int i = 0; i < 12; i++)
                    {
                        push[i] = 0;
                    }
                    push[i] = 1;
                }
            }

            // else if (CheckCollisionPointCircle(mouse_position, positionR1, radius))
            // {
            //     is_dragging = true;
            //     anchor_point = positionR1;
            //     player_speed = Vector2Zero();
            // }
            // else if (CheckCollisionPointCircle(mouse_position, positionR2, radius))
            // {
            //     is_dragging = true;
            //     anchor_point = positionR2;
            //     player_speed = Vector2Zero();
            // }
            // else if (CheckCollisionPointCircle(mouse_position, positionR3, radius))
            // {
            //     is_dragging = true;
            //     anchor_point = positionR3;
            //     player_speed = Vector2Zero();
            // }
            // else if (CheckCollisionPointCircle(mouse_position, positionR4, radius))
            // {
            //     is_dragging = true;
            //     anchor_point = positionR4;
            //     player_speed = Vector2Zero();
            // }
            // else if (CheckCollisionPointCircle(mouse_position, positionR5, radius))
            // {
            //     is_dragging = true;
            //     anchor_point = positionR5;
            //     player_speed = Vector2Zero();
            // }
            // else if (CheckCollisionPointCircle(mouse_position, positionR6, radius))
            // {
            //     is_dragging = true;
            //     anchor_point = positionR6;
            //     player_speed = Vector2Zero();
            // }
        }

        if (is_dragging)
        {
            dragged = Vector2Subtract(mouse_position, anchor_point);
            power = power_speed * Vector2Length(dragged);

            if (power > max_power)
            {
                power = max_power;
            }
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && is_dragging)
        {
            is_dragging = false;
            // dragged = Vector2Subtract(mouse_position, anchor_point);
            float dragged_distance = Vector2Length(dragged);
            if (dragged_distance > 10)
            {
                Vector2 dragged_direction = Vector2Normalize(dragged);

                launch_direction = Vector2Negate(dragged_direction);
                for (int i = 0; i < 12; i++)
                {

                    player_speed[i] = Vector2Scale(launch_direction, power);
                }
            }
            // power = 0;
        }
        if (!is_dragging)
        {

            for (int i = 0; i < 12; i++)
            {

                if (push[i])
                {
                    *positions[i] = Vector2Add(*positions[i], Vector2Scale(player_speed[i], dt));
                }
                // else if (push[1])
                // {
                //     positionB2 = Vector2Add(positionB2, Vector2Scale(player_speed, dt));
                // }
                // else if (push[2])
                // {
                //     positionB3 = Vector2Add(positionB3, Vector2Scale(player_speed, dt));
                // }
                // else if (push[3])
                // {
                //     positionB4 = Vector2Add(positionB4, Vector2Scale(player_speed, dt));
                // }
                // else if (push[4])
                // {
                //     positionB5 = Vector2Add(positionB5, Vector2Scale(player_speed, dt));
                // }
                // else if (push[5])
                // {
                //     positionB6 = Vector2Add(positionB6, Vector2Scale(player_speed, dt));
                // }
                player_speed[i] = Vector2Scale(player_speed[i], 1.0 - (1 * dt));
                if (((*positions[i]).x - radius < 50.2) || ((*positions[i]).x + radius > 1450.4))
                {
                    player_speed[i].x *= -1;
                }
                if (((*positions[i]).y - radius < 120) || ((*positions[i]).y + radius > 680))
                {
                    player_speed[i].y *= -1;
                    
                }
            }

            // if ((positionB1.x - radius < 50.2) || (positionB1.x + radius > 1450.4))
            // {
            //     player_speed.x *= -1;
            //     positionB1.x = Clamp(positionB1.x, radius, 1450 - radius);
            // }
            // if ((positionB1.y - radius < 120) || (positionB1.y + radius > 680))
            // {
            //     player_speed.y *= -1;
            //     positionB1.y = Clamp(positionB1.y, radius, 680 - radius);
            // }
            // if ((positionB2.x - radius < 50.2) || (positionB2.x + radius > 1450.4))
            // {
            //     player_speed.x *= -1;
            //     positionB2.x = Clamp(positionB2.x, radius, 1450 - radius);
            // }
            // if ((positionB2.y - radius < 120) || (positionB2.y + radius > 680))
            // {
            //     player_speed.y *= -1;
            //     positionB2.y = Clamp(positionB2.y, radius, 680 - radius);
            // }
            // if ((positionB3.x - radius < 50.2) || (positionB3.x + radius > 1450.4))
            // {
            //     player_speed.x *= -1;
            //     positionB3.x = Clamp(positionB3.x, radius, 1450 - radius);
            // }
            // if ((positionB3.y - radius < 120) || (positionB3.y + radius > 680))
            // {
            //     player_speed.y *= -1;
            //     positionB3.y = Clamp(positionB3.y, radius, 680 - radius);
            // }
            // if ((positionB4.x - radius < 50.2) || (positionB4.x + radius > 1450.4))
            // {
            //     player_speed.x *= -1;
            //     positionB4.x = Clamp(positionB4.x, radius, 1450 - radius);
            // }
            // if ((positionB4.y - radius < 120) || (positionB4.y + radius > 680))
            // {
            //     player_speed.y *= -1;
            //     positionB4.y = Clamp(positionB4.y, radius, 680 - radius);
            // }
            // if ((positionB5.x - radius < 50.2) || (positionB5.x + radius > 1450.4))
            // {
            //     player_speed.x *= -1;
            //     positionB5.x = Clamp(positionB5.x, radius, 1450 - radius);
            // }
            // if ((positionB5.y - radius < 120) || (positionB5.y + radius > 680))
            // {
            //     player_speed.y *= -1;
            //     positionB5.y = Clamp(positionB5.y, radius, 680 - radius);
            // }
            // if ((positionB6.x - radius < 50.2) || (positionB6.x + radius > 1450.4))
            // {
            //     player_speed.x *= -1;
            //     positionB6.x = Clamp(positionB6.x, radius, 1450 - radius);
            // }
            // if ((positionB6.y - radius < 120) || (positionB6.y + radius > 680))
            // {
            //     player_speed.y *= -1;
            //     positionB6.y = Clamp(positionB6.y, radius, 680 - radius);
            // }
        }

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
            DrawCircleV(positionB1, radius, BLUE);
            DrawCircleV(positionB2, radius, BLUE);
            DrawCircleV(positionB3, radius, BLUE);
            DrawCircleV(positionB4, radius, BLUE);
            DrawCircleV(positionB5, radius, BLUE);
            DrawCircleV(positionB6, radius, BLUE);
            DrawCircleV(positionR1, radius, RED);
            DrawCircleV(positionR2, radius, RED);
            DrawCircleV(positionR3, radius, RED);
            DrawCircleV(positionR4, radius, RED);
            DrawCircleV(positionR5, radius, RED);
            DrawCircleV(positionR6, radius, RED);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
