#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#define height 800
#define width 1500
#define border1X 50.2
#define border2X 1450.4
#define border1Y 120
#define border2Y 680
#define radius 50
#define ballRadius 30

int main(void)
{
	InitWindow(width, height, "Game");
	Texture2D football_Field = LoadTexture("resources/Football_field.png");
	Texture2D intro = LoadTexture("resources/Start1.png");
	Texture2D option = LoadTexture("resources/Option.png");

	int starting_click = 0;
	int option_click = 0;
	int turn = 1;

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

	Vector2 ball = {749.5, 382};

	Vector2 player_speed[12] = {0};

	Vector2 ballSpeed = Vector2Zero();

	Vector2 launch_direction = Vector2Zero();

	bool is_dragging = false;
	Vector2 dragged = Vector2Zero();

	bool shot_in_progress = false;

	float power = 0.0;
	float max_power = 1000.0;
	float max_speed = 400.0;
	float power_speed = 7;
	Vector2 anchor_point = Vector2Zero();
	int push[12] = {0};
	Vector2 *positions[12] = {&positionB1, &positionB2, &positionB3, &positionB4, &positionB5, &positionB6, &positionR1, &positionR2, &positionR3, &positionR4, &positionR5, &positionR6};

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
				if (CheckCollisionPointCircle(mouse_position, *positions[i], radius) && ((turn % 2 == 1 && i < 6) || (turn % 2 == 0 && i >= 6)))
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
					if (CheckCollisionCircles(*positions[i], radius, *positions[j], radius))
					{
						Vector2 normal = Vector2Normalize(Vector2Subtract(*positions[j], *positions[i]));

						Vector2 relativeVelocity = Vector2Subtract(player_speed[i], player_speed[j]);
						float velAlongNormal = Vector2DotProduct(relativeVelocity, normal);

						if (velAlongNormal > 0)
						{
							float restitution = 0.4;
							float impulseMagnitude = (1.0 + restitution) * velAlongNormal;

							impulseMagnitude /= 2.0;

							Vector2 impulse = Vector2Scale(normal, impulseMagnitude);

							player_speed[i] = Vector2Subtract(player_speed[i], impulse);
							player_speed[j] = Vector2Add(player_speed[j], impulse);
						}
					}
				}
				if (CheckCollisionCircles(*positions[i], radius, ball, ballRadius))
				{
					Vector2 normal = Vector2Normalize(Vector2Subtract(ball, *positions[i]));

					Vector2 relativeVelocity = Vector2Subtract(player_speed[i], ballSpeed);
					float velAlongNormal = Vector2DotProduct(relativeVelocity, normal);

					if (velAlongNormal > 0)
					{
						float restitution = 0.4;
						float impulseMagnitude = (1.0 + restitution) * velAlongNormal;

						impulseMagnitude /= 10.66;

						Vector2 impulse = Vector2Scale(normal, impulseMagnitude);

						player_speed[i] = Vector2Subtract(player_speed[i], Vector2Scale(impulse, 1.0f));
						ballSpeed = Vector2Add(ballSpeed, Vector2Scale(impulse, 9.66f));
					}
				}
			}
			for (int i = 0; i < 12; i++)
			{
				*positions[i] = Vector2Add(
					*positions[i],
					Vector2Scale(player_speed[i], dt));
				player_speed[i] = Vector2Scale(player_speed[i], 1.0 - (1 * dt));

				if (((*positions[i]).x - radius < border1X) || ((*positions[i]).x + radius > border2X))
				{
					player_speed[i].x *= -1;
				}

				if (((*positions[i]).y - radius < border1Y) || ((*positions[i]).y + radius > border2Y))
				{
					player_speed[i].y *= -1;
				}
			}
			
			ball = Vector2Add(ball, Vector2Scale(ballSpeed, dt));
			ballSpeed = Vector2Scale(ballSpeed, 1.0 - (1 * dt));
			// For ball
			if (((ball).x - ballRadius < border1X) || ((ball).x + ballRadius > border2X))
			{
				ballSpeed.x *= -1;
			}

			if (((ball).y - ballRadius < border1Y) || ((ball).y + ballRadius > border2Y))
			{
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

		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (!starting_click)
		{
			DrawTexture(intro, 0, 0, WHITE);
			starting_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		}
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
			DrawCircleV(ball, ballRadius, RAYWHITE);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}