#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "raylib - Slingshot Mechanics");

    // Circular Object Properties
    Vector2 ballPosition = { 400.0f, 300.0f };
    Vector2 ballVelocity = Vector2Zero();
    float ballRadius = 25.0f;
    Color ballColor = MAROON;

    // Slingshot State Properties
    bool isDragging = false;
    Vector2 dragAnchor = Vector2Zero(); // Store where the drag started
    float currentPower = 0.0f;
    float maxPower = 500.0f;           // Cap to prevent launching too fast
    float powerMultiplier = 4.0f;      // Converts screen drag distance to physical speed

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();
        // ---- 1. INPUT HANDLING & STATE LOGIC ----
        
        // MOUSE CLICKED: Check if clicking inside the ball
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle(mousePos, ballPosition, ballRadius)) {
                isDragging = true;
                dragAnchor = ballPosition; // Lock the anchor point to the ball center
                ballVelocity = Vector2Zero(); // Stop any current movement
            }
        }

        // MOUSE HELD: Calculate pulling vector and power level
        if (isDragging) {
            // Find vector from anchor point to current mouse position
            Vector2 pullVector = Vector2Subtract(mousePos, dragAnchor);
            
            // Power matches the drag distance, capped at max threshold
            currentPower = Vector2Length(pullVector) * powerMultiplier;
            if (currentPower > maxPower) currentPower = maxPower;

            // Optional visual modifier: Snap ball slightly along the drag line
            // ballPosition = Vector2Add(dragAnchor, Vector2Scale(Vector2Normalize(pullVector), currentPower / powerMultiplier));
        }

        // MOUSE RELEASED: Calculate launch vector and apply velocity
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && isDragging) {
            isDragging = false;

            Vector2 pullVector = Vector2Subtract(mousePos, dragAnchor);
            float pullDistance = Vector2Length(pullVector);

            if (pullDistance > 5.0f) { // Prevent tiny accidental dead-zone clicks
                // Get clean direction of drag
                Vector2 pullDirection = Vector2Normalize(pullVector);
                
                // Invert direction to fire OPPOSITE of drag vector
                Vector2 launchDirection = Vector2Negate(pullDirection);

                // Velocity = Launch Direction * Scaled Power
                ballVelocity = Vector2Scale(launchDirection, currentPower);
            } else {
                // If let go without a notable drag radius, snap back to center
                ballPosition = dragAnchor;
            }
            
            currentPower = 0.0f; // Reset gauge
        }

        // ---- 2. PHYSICS UPDATE ----
        if (!isDragging) {
            // Move object based on launch velocity vectors
            ballPosition = Vector2Add(ballPosition, Vector2Scale(ballVelocity, dt));

            // Simple friction dampening so the ball gradually slows down
            ballVelocity = Vector2Scale(ballVelocity, 1.0f - (0.9f * dt));

            // Screen boundary wall collisions
            if ((ballPosition.x - ballRadius < 0) || (ballPosition.x + ballRadius > screenWidth)) {
                ballVelocity.x *= -0.8f; // Bounce with minor energy dissipation
                ballPosition.x = Clamp(ballPosition.x, ballRadius, screenWidth - ballRadius);
            }
            if ((ballPosition.y - ballRadius < 0) || (ballPosition.y + ballRadius > screenHeight)) {
                ballVelocity.y *= -0.8f;
                ballPosition.y = Clamp(ballPosition.y, ballRadius, screenHeight - ballRadius);
            }
        }

        // ---- 3. RENDER DRAWING ----
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw Aiming Guide & Slingshot Line if actively dragging
            if (isDragging) {
                // Draw line showing drag vector
                DrawLineV(dragAnchor, mousePos, LIGHTGRAY);
                
                // Draw target trajectory guide line pointing in opposite launch direction
                Vector2 pullVector = Vector2Subtract(mousePos, dragAnchor);
                Vector2 launchDir = Vector2Negate(Vector2Normalize(pullVector));
                Vector2 visualGuideEnd = Vector2Add(dragAnchor, Vector2Scale(launchDir, currentPower / powerMultiplier));
                DrawLineV(dragAnchor, visualGuideEnd, LIME);

                // Render dynamic text detailing active gauge status
                DrawText(TextFormat("LAUNCH POWER: %.0f / %.0f", currentPower, maxPower), 20, 50, 20, DARKGRAY);
            }

            // Draw primary circular gameplay object
            DrawCircleV(ballPosition, ballRadius, ballColor);

            DrawText("Click, pull back, and release the circle to launch!", 20, 20, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
