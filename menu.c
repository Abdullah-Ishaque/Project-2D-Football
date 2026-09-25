#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#define height 800
#define width 1500
#define border1X 50.2
#define border2X 1450.4
#define border1Y 120
#define border2Y 680
#define radius 40
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
    GAMEPLAY
} Screen;
Screen screen = STARTING;

int main(void)
{
    InitWindow(width, height, "Game");
    Texture2D football_Field = LoadTexture("resources/Football_field.png");
    Texture2D intro = LoadTexture("resources/Start1.png");
    Texture2D FormationB[5], FormationR[5];
    int menuWidth = 700;
    int menuHeight = 500;
    int buttonWidth = 320;
    int buttonHeight = 70;

    int menuX = (1500 - menuWidth) / 2;
    int menuY = (800 - menuHeight) / 2;
    int formationInitial = 110;

    // Custom made color
    Color screenBackground = {10, 15, 25, 255};
    Color menuBackground = {20, 25, 35, 245};
    Color playButtonColor, tutorialButtonColor, aboutButtonColor;
    Color buttonBorderColor = {35, 45, 60, 255};
    Color buttonBorderHoverColor = {35, 45, 100, 255};
    Color text = {50, 60, 120, 240};
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

    Rectangle playButton = {590, 300, 320, 70};

    Rectangle tutorialButton = {590, 390, 320, 70};

    Rectangle aboutButton = {590, 480, 320, 70};

    int formationChoice[2] = {0, 0};
    int currentPicker = 0;
    for (int i = 0; i < 5; i++)
    {
        FormationB[i] = LoadTexture(TextFormat("resources/blue-formation%d.png", i + 1));
        FormationR[i] = LoadTexture(TextFormat("resources/red-formation%d.png", i + 1));
    }
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mouse_position = GetMousePosition();

        if (screen == STARTING)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                screen = MENU;
            }
        }
        else if (screen == MENU)
        {
            playButtonColor = CheckCollisionPointRec(mouse_position, playButton) ? buttonBorderHoverColor : buttonBorderColor;
            tutorialButtonColor = CheckCollisionPointRec(mouse_position, tutorialButton) ? buttonBorderHoverColor : buttonBorderColor;
            aboutButtonColor = CheckCollisionPointRec(mouse_position, aboutButton) ? buttonBorderHoverColor : buttonBorderColor;
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
        }
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
                                for (int m = 0, n = 5; m < PLAYER_COUNT; m++, n++)
                                {
                                    positions[n] = redFormations[j][m];
                                }
                                screen = GAMEPLAY;
                            }
                    }
                }
            }
        }
        else if (screen == TUTORIAL)
        {
        }
        else if (screen == ABOUT)
        {
        }
        else if (screen == GAMEPLAY)
        {
        }

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
            DrawText("MAIN MENU", 635, 180, 42, text);
            DrawRectangleRoundedLinesEx(playButton, 0.8, 0.8, 5.0, playButtonColor);
            DrawRectangleRoundedLinesEx(tutorialButton, 0.8, 0.8, 5.0, tutorialButtonColor);
            DrawRectangleRoundedLinesEx(aboutButton, 0.8, 0.8, 5.0, aboutButtonColor);
            DrawText("PLAY", 712, 318, 32, text);
            DrawText("TUTORIAL", 660, 408, 32, text);
            DrawText("ABOUT US", 670, 498, 32, text);
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
        }
        else if (screen == ABOUT)
        {
            ClearBackground(screenBackground);
        }
        else if (screen == TUTORIAL)
        {
            ClearBackground(screenBackground);
        }
        else if (screen == GAMEPLAY)
        {
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}