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
    Color aboutText = {83, 83, 181,245};
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

    bool is_dragging = false;
    Vector2 dragged = Vector2Zero();

    bool shot_in_progress = false;

    float power = 0.0;
    float max_power = 1000.0f;
    float max_speed = 400.0f;
    float power_speed = 7;
    Vector2 anchor_point = Vector2Zero();
    int push[12] = {0};

    Rectangle playButton = {590, 245, 320, 70};
    Rectangle tutorialButton = {590, 325, 320, 70};
    Rectangle aboutButton = {590, 405, 320, 70};
    Rectangle creditButton = {590, 485, 320, 70};
    Rectangle backButton = {30, 715, 180, 55};

    int formationChoice[2] = {0, 0};
    int currentPicker = 0;
    for (int i = 0; i < 5; i++)
    {
        FormationB[i] = LoadTexture(TextFormat("resources/blue-formation%d.png", i + 1));
        FormationR[i] = LoadTexture(TextFormat("resources/red-formation%d.png", i + 1));
    }

    SetTargetFPS(60);

    float fieldHeight = height - 200;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mouse_position = GetMousePosition();

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

            DrawText("Developers of Football 2D",555, 100, 28, LIGHTGRAY);

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
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}