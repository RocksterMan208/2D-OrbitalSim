#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

constexpr int windowWidth = 1920;
constexpr int windowHeight = 1080;
const std::string windowTitle = "Epic Window";

const float gravConst = 10.0f;

int timeWarp = 1;

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.offset = {windowWidth/2, windowHeight/2};
    camera.rotation = 0;
    camera.target = {windowWidth/2, windowHeight/2};
    camera.zoom = 1.0f;

    Planet center;
    center.mass = 1000000.0f;
    center.radius = 100.0f;
    center.pos = {960, 540};
    center.color = ORANGE;

    Planet satellite;
    satellite.mass = 3333.3f;
    satellite.radius = 20.0f;
    satellite.pos = {1140, 540};
    satellite.color = BLUE;

    float speedCirc = 310.0f;

    satellite.vel = {0, -speedCirc};

    while (!WindowShouldClose())
    {
        satellite.update(gravConst, center, timeWarp*GetFrameTime());

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouseChange = GetMouseDelta(); // Getting mouse delta for movement
            camera.target = Vector2Add(camera.target, Vector2Scale(mouseChange, -1.0f / camera.zoom)); // Uses the mouse delta to move the camera in the direciton of movement
        }
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f)); // Uses log for consistent mouse wheel zooming

        if (IsKeyDown(KEY_UP)) satellite.vel.y -= 1.0f;
        if (IsKeyDown(KEY_DOWN)) satellite.vel.y += 1.0f;
        if (IsKeyDown(KEY_RIGHT)) satellite.vel.x -= 1.0f;
        if (IsKeyDown(KEY_LEFT)) satellite.vel.x += 1.0f;

        if (IsKeyPressed(KEY_PERIOD)) timeWarp += 1;
        if (IsKeyPressed(KEY_COMMA)) timeWarp -= 1;

        BeginDrawing();
        ClearBackground(RAYWHITE);
            BeginMode2D(camera);

            satellite.drawPredictedOrbit(gravConst, center);

            center.render();
            satellite.render();


            EndMode2D();

            DrawFPS(10,10);
            
            std::string text = std::to_string(timeWarp);

            DrawText(text.c_str(), 10, 40, 16, BLACK);

        EndDrawing();
    }

    return 0;
}