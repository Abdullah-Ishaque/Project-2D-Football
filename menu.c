#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#define height 800
#define width 1500
#define border1X 50.2
#define border2X 1450.4
#define border1Y 120
#define border2Y 680
#define playerRadius 40
#define ballRadius 25
#define goalTop 290
#define goalBottom 570
#define PLAYER_COUNT 6
#define FORMATION_COUNT 5
#define buttonStartingPosition 590
#define formationWidth 240
#define formationHeight 400

typedef enum
{
    STARTING,
    MENU,
    PLAY,
    TUTORIAL,
    ABOUT,
    CREDIT,
    GAMEPLAY
} Screen;
Screen screen = STARTING;

int main(void)
{
    InitWindow(width, height, "Game");
    Texture2D football_Field = LoadTexture("resources/Football_field.png");
    Texture2D intro = LoadTexture("resources/Start1.png");
    Texture2D tutorial = LoadTexture("resources/Tutorial.png");
    Texture2D sakib = LoadTexture("resources/Sakib_36.png");
    Texture2D ishaque = LoadTexture("resources/Ishaque_58.png");
    Texture2D FormationB[5], FormationR[5];
    for (int i = 0; i < 5; i++)
    {
        FormationB[i] = LoadTexture(TextFormat("resources/blue-formation%d.png", i + 1));
        FormationR[i] = LoadTexture(TextFormat("resources/red-formation%d.png", i + 1));
    }
    
    int turn = 1;

    int blueScore = 0;
    int redScore = 0;

    int menuWidth = 700;
    int menuHeight = 500;
    int buttonWidth = 320;
    int buttonHeight = 70;
    int backButtonWidth = 180;
    int backButtonHeight = 55;

    int menuX = (1500 - menuWidth) / 2;
    int menuY = (800 - menuHeight) / 2;
    int formationInitial = 110;

    // Custom made color
    Color screenBackground = {10, 15, 25, 255};
    Color menuBackground = {20, 25, 35, 245};
    Color playButtonColor, tutorialButtonColor, aboutButtonColor, backButtonColor, creditButtonColor;
    Color buttonBorderColor = {35, 45, 60, 255};
    Color buttonBorderHoverColor = {35, 45, 100, 255};
    Color textColor = {50, 60, 120, 240};
    Color backButtonColorUni = {200, 100, 40, 245};
    Color aboutText = {83, 83, 181, 245};
    //
    Rectangle formations[FORMATION_COUNT];
    Vector2 positions[12];
    for (int i = 0; i < FORMATION_COUNT; i++)
    {
        formations[i] = (Rectangle){formationInitial + (i * 260), 170, 240, 400};
    }
    Vector2 blueFormations[FORMATION_COUNT][PLAYER_COUNT] =
        {

            {{90.2, 405.75},
             {289.15, 255.75},
             {289.15, 555.75},
             {587.05, 255.75},
             {438.1, 405.75},
             {587.05, 555.75}},
            {{90.2, 405.75},
             {290, 220},
             {290, 405.75},
             {290, 590},
             {470, 405.75},
             {620, 405.75}},
            {{90.2, 405.75},
             {285, 270},
             {285, 540},
             {460, 270},
             {460, 540},
             {620, 405.75}},
            {{90.2, 405.75},
             {300, 405.75},
             {480, 220},
             {480, 405.75},
             {480, 590},
             {635, 405.75}},
            {{90.2, 405.75},
             {300, 405.75},
             {455, 405.75},
             {620, 220},
             {620, 405.75},
             {620, 590}}};
    Vector2 redFormations[FORMATION_COUNT][PLAYER_COUNT];
    for (int f = 0; f < FORMATION_COUNT; f++)
    {
        for (int g = 0; g < PLAYER_COUNT; g++)
        {
            redFormations[f][g].x =
                width - blueFormations[f][g].x;

            redFormations[f][g].y =
                blueFormations[f][g].y;
        }
    }
    Vector2 ball = {750.3, 400};

    Vector2 player_speed[12] = {0};

    Vector2 ballSpeed = Vector2Zero();

    Vector2 launch_direction = Vector2Zero();

    Vector2 anchor_point = Vector2Zero();

    bool is_dragging = false;
    Vector2 dragged = Vector2Zero();

    bool shot_in_progress = false;

    float power = 0.0;
    float max_power = 1000.0f;
    float max_speed = 400.0f;
    float power_speed = 7;
    int push[12] = {0};

    Rectangle playButton = {590, 245, 320, 70};
    Rectangle tutorialButton = {590, 325, 320, 70};
    Rectangle aboutButton = {590, 405, 320, 70};
    Rectangle creditButton = {590, 485, 320, 70};
    Rectangle backButton = {30, 715, 180, 55};

    int formationChoice[2] = {0, 0};
    int currentPicker = 0;

    SetTargetFPS(60);

    float fieldHeight = height - 200;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mouse_position = GetMousePosition();
        float anchor = Vector2Length(anchor_point);
        float launch = Vector2Length(launch_direction);
        float endx = 2*anchor_point.x-mouse_position.x;
        float endy = 2*anchor_point.y-mouse_position.y;
        Vector2 end = {endx,endy};
        if(Vector2Length(end)>20){
            endx = (anchor_point.x + endx)/2;
            endy = (anchor_point.y + endy)/2;
        }

        backButtonColor = CheckCollisionPointRec(mouse_position, backButton) ? backButtonColorUni : BLUE;
        if (screen == STARTING)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                screen = MENU;
            }
        }
        // =======================================================================MENU==================================================================
        else if (screen == MENU)
        {
            playButtonColor = CheckCollisionPointRec(mouse_position, playButton) ? buttonBorderHoverColor : buttonBorderColor;
            tutorialButtonColor = CheckCollisionPointRec(mouse_position, tutorialButton) ? buttonBorderHoverColor : buttonBorderColor;
            aboutButtonColor = CheckCollisionPointRec(mouse_position, aboutButton) ? buttonBorderHoverColor : buttonBorderColor;
            creditButtonColor = CheckCollisionPointRec(mouse_position, creditButton) ? buttonBorderHoverColor : buttonBorderColor;
            if (CheckCollisionPointRec(mouse_position, playButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = PLAY;
                }
            }
            else if (CheckCollisionPointRec(mouse_position, tutorialButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = TUTORIAL;
                }
            }
            else if (CheckCollisionPointRec(mouse_position, aboutButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = ABOUT;
                }
            }
            else if (CheckCollisionPointRec(mouse_position, creditButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = CREDIT;
                }
            }
        }
        // =======================================================================PLAY==================================================================
        else if (screen == PLAY)
        {
            for (int j = 0; j < FORMATION_COUNT; j++)
            {
                if (CheckCollisionPointRec(mouse_position, formations[j]))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (!currentPicker)
                        {
                            for (int l = 0; l < PLAYER_COUNT; l++)
                            {
                                positions[l] = blueFormations[j][l];
                            }
                            currentPicker = 1;
                        }
                        else
                        {
                            for (int m = 0, n = 6; m < PLAYER_COUNT; m++, n++)
                            {
                                positions[n] = redFormations[j][m];
                            }
                            if (CheckCollisionPointRec(mouse_position, backButton))
                            {
                                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                                {
                                    screen = PLAY;
                                }
                            }
                            else
                                screen = GAMEPLAY;
                        }
                    }
                }
                else
                {
                    if (CheckCollisionPointRec(mouse_position, backButton))
                    {
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentPicker == 0)
                        {
                            screen = MENU;
                            break;
                        }
                        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currentPicker == 1)
                        {
                            currentPicker = 0;
                            screen = PLAY;
                            break;
                        }
                    }
                }
            }
        }
        // =======================================================================TUTORIAL==================================================================
        else if (screen == TUTORIAL)
        {
            DrawTexture(tutorial, 0, 0, RAYWHITE);
            if (CheckCollisionPointRec(mouse_position, backButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = MENU;
                }
            }
        }

        // =======================================================================ABOUT==================================================================

        else if (screen == ABOUT)
        {
            if (CheckCollisionPointRec(mouse_position, backButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = MENU;
                }
            }
        }
        // =======================================================================CREDIT==================================================================
        else if (screen == CREDIT)
        {
            if (CheckCollisionPointRec(mouse_position, backButton))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    screen = MENU;
                }
            }
        }

        // =======================================================================GAMEPLAY==================================================================
        else if (screen == GAMEPLAY)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                for (int i = 0; i < 12; i++)
                {
                    if (CheckCollisionPointCircle(mouse_position, positions[i], playerRadius) && ((turn % 2 == 1 && i < 6) || (turn % 2 == 0 && i >= 6)))
                    {
                        is_dragging = true;
                        anchor_point = positions[i];
                        player_speed[i] = Vector2Zero();
                        for (int i = 0; i < 12; i++)
                        {
                            push[i] = 0;
                        }
                        push[i] = 1;
                    }
                }
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
                float dragged_distance = Vector2Length(dragged);
                if (dragged_distance > 10)
                {
                    Vector2 dragged_direction = Vector2Normalize(dragged);

                    launch_direction = Vector2Negate(dragged_direction);
                    for (int i = 0; i < 12; i++)
                    {
                        if (push[i])
                        {
                            player_speed[i] = Vector2Scale(launch_direction, power);
                        }
                    }
                    shot_in_progress = true;
                }
            }
            if (!is_dragging)
            {

                for (int i = 0; i < 12; i++)
                {
                    for (int j = i + 1; j < 12; j++)
                    {
                        if (CheckCollisionCircles(positions[i], playerRadius, positions[j], playerRadius))
                        {
                            Vector2 normal = Vector2Normalize(Vector2Subtract(positions[j], positions[i]));

                            Vector2 relativeVelocity = Vector2Subtract(player_speed[i], player_speed[j]);
                            float velAlongNormal = Vector2DotProduct(relativeVelocity, normal);

                            if (velAlongNormal > 0)
                            {
                                float restitution = 0.4f;
                                float impulseMagnitude = (1.0f + restitution) * velAlongNormal;

                                impulseMagnitude /= 2.0f;

                                Vector2 impulse = Vector2Scale(normal, impulseMagnitude);

                                player_speed[i] = Vector2Subtract(player_speed[i], impulse);
                                player_speed[j] = Vector2Add(player_speed[j], impulse);
                            }
                        }
                    }
                    if (CheckCollisionCircles(positions[i], playerRadius, ball, ballRadius))
                    {
                        Vector2 normal = Vector2Normalize(Vector2Subtract(ball, positions[i]));

                        Vector2 relativeVelocity = Vector2Subtract(player_speed[i], ballSpeed);
                        float velAlongNormal = Vector2DotProduct(relativeVelocity, normal);

                        if (velAlongNormal > 0)
                        {
                            float restitution = 0.4f;
                            float impulseMagnitude = (1.0f + restitution) * velAlongNormal;

                            impulseMagnitude /= 10.66f;

                            Vector2 impulse = Vector2Scale(normal, impulseMagnitude);

                            player_speed[i] = Vector2Subtract(player_speed[i], Vector2Scale(impulse, 1.0f));
                            ballSpeed = Vector2Add(ballSpeed, Vector2Scale(impulse, 9.66f));
                        }
                    }
                    anchor=0;
                    launch = 0;
                }
                for (int i = 0; i < 12; i++)
                {
                    positions[i] = Vector2Add(
                        positions[i],
                        Vector2Scale(player_speed[i], dt));
                    player_speed[i] = Vector2Scale(player_speed[i], 1.0f - (1 * dt));

                    if ((positions[i]).x - playerRadius < border1X)
                    {
                        (positions[i]).x = border1X + playerRadius;
                        player_speed[i].x *= -1;
                    }
                    else if ((positions[i]).x + playerRadius > border2X)
                    {
                        (positions[i]).x = border2X - playerRadius;
                        player_speed[i].x *= -1;
                    }

                    if ((positions[i]).y - playerRadius < border1Y)
                    {
                        (positions[i]).y = border1Y + playerRadius;
                        player_speed[i].y *= -1;
                    }
                    else if ((positions[i]).y + playerRadius > border2Y)
                    {
                        (positions[i]).y = border2Y - playerRadius;
                        player_speed[i].y *= -1;
                    }
                }

                ball = Vector2Add(ball, Vector2Scale(ballSpeed, dt));
                ballSpeed = Vector2Scale(ballSpeed, 1.0f - (1 * dt));
                // For ball

                if (ball.x - ballRadius < border1X)
                {
                    if (ball.y - ballRadius > goalTop &&
                        ball.y + ballRadius < goalBottom)
                    {
                        redScore++;

                        ball = (Vector2){749.5, 382};
                        ballSpeed = Vector2Zero();
                    }
                    else
                    {
                        ball.x = border1X + ballRadius;
                        ballSpeed.x *= -1;
                    }
                }
                else if (ball.x + ballRadius > border2X)
                {
                    if (ball.y - ballRadius > goalTop &&
                        ball.y + ballRadius < goalBottom)
                    {
                        blueScore++;

                        ball = (Vector2){749.5, 382};
                        ballSpeed = Vector2Zero();
                    }
                    else
                    {
                        ball.x = border2X - ballRadius;
                        ballSpeed.x *= -1;
                    }
                }

                if (ball.y - ballRadius < border1Y)
                {
                    ball.y = border1Y + ballRadius;
                    ballSpeed.y *= -1;
                }
                else if (ball.y + ballRadius > border2Y)
                {
                    ball.y = border2Y - ballRadius;
                    ballSpeed.y *= -1;
                }
            }

            if (shot_in_progress)
            {
                bool player_stopped = true;

                for (int i = 0; i < 12; i++)
                {
                    if (push[i] && Vector2Length(player_speed[i]) > 5)
                    {
                        player_stopped = false;
                    }
                }

                if (player_stopped)
                {
                    turn++;
                    shot_in_progress = false;

                    for (int i = 0; i < 12; i++)
                        push[i] = 0;
                }
            }
        }

        // =======================================================================DRAWING==================================================================

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (screen == STARTING)
        {
            DrawTexture(intro, 0, 0, WHITE);
        }
        else if (screen == MENU)
        {
            ClearBackground(screenBackground);
            DrawRectangle(menuX, menuY, menuWidth, menuHeight, menuBackground);
            DrawText("MAIN MENU", 635, 175, 42, RAYWHITE);
            DrawRectangleRoundedLinesEx(playButton, 0.8, 0.8, 5.0, playButtonColor);
            DrawRectangleRoundedLinesEx(tutorialButton, 0.8, 0.8, 5.0, tutorialButtonColor);
            DrawRectangleRoundedLinesEx(aboutButton, 0.8, 0.8, 5.0, aboutButtonColor);
            DrawRectangleRoundedLinesEx(creditButton, 0.8, 0.8, 5.0, creditButtonColor);
            DrawText("PLAY", 712, 264, 32, textColor);
            DrawText("TUTORIAL", 660, 344, 32, textColor);
            DrawText("ABOUT US", 670, 424, 32, textColor);
            DrawText("CREDIT", 690, 504, 32, textColor);
        }
        else if (screen == PLAY)
        {
            ClearBackground(screenBackground);
            if (!currentPicker)
            {
                for (int i = 0; i < FORMATION_COUNT; i++)
                {
                    DrawTexture(FormationB[i], formationInitial + (i * 260), 170, WHITE);
                }
            }
            else
            {
                for (int i = 0; i < FORMATION_COUNT; i++)
                {
                    DrawTexture(FormationR[i], formationInitial + (i * 260), 170, WHITE);
                }
            }
            DrawRectangleRoundedLinesEx(backButton, 0.8, 0.8, 3.0, backButtonColor);
            DrawText("BACK", 82, 728, 30, RAYWHITE);
        }
        else if (screen == TUTORIAL)
        {
            ClearBackground(screenBackground);
            DrawRectangleRoundedLinesEx(backButton, 0.8, 0.8, 3.0, backButtonColor);
            DrawText("BACK", 82, 728, 30, RAYWHITE);
        }
        else if (screen == ABOUT)
        {
            ClearBackground(screenBackground);
            DrawRectangleRoundedLinesEx(backButton, 0.8, 0.8, 3.0, backButtonColor);
            DrawText("BACK", 82, 728, 30, RAYWHITE);

            DrawText("ABOUT US", 635, 50, 42, RAYWHITE);

            DrawText("Developers of Football 2D", 555, 100, 28, LIGHTGRAY);

            DrawTexture(sakib, 250, 140, WHITE);
            DrawTexture(ishaque, 950, 140, WHITE);

            DrawText("SAKIB", 350, 545, 30, aboutText);
            DrawText("ISHAQUE", 1040, 545, 30, aboutText);

            DrawText("Roll: 2505036", 345, 585, 26, aboutText);
            DrawText("Roll: 2505058", 1040, 585, 26, aboutText);
        }
        else if (screen == CREDIT)
        {
            ClearBackground(screenBackground);
            DrawRectangleRoundedLinesEx(backButton, 0.8, 0.8, 3.0, backButtonColor);
            DrawText("BACK", 82, 728, 30, RAYWHITE);
        }
        else if (screen == GAMEPLAY)
        {
            DrawTexture(football_Field, 0, 0, WHITE);
            for (int i = 0; i < 12; i++)
            {
                DrawCircleV(positions[i], playerRadius, (i < 6) ? BLUE : RED);
            }
            DrawCircleV(ball, ballRadius, RAYWHITE);
            if(anchor != 0){
                DrawLineV(mouse_position,anchor_point,GRAY);
                
            }
            if(launch != 0){
                DrawLine(anchor_point.x,anchor_point.y,endx,endy,GRAY);
                
            }
            
            DrawText("Football 2D", 650, 50, 50, BLUE);
            DrawText(TextFormat("Blue: %d.   Red: %d", blueScore, redScore), 620, 100, 30, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}