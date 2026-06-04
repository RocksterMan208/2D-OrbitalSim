#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

constexpr int windowWidth = 1920;
constexpr int windowHeight = 1080;
const std::string windowTitle = "Epic Window";

const float gravConst = 10.0f;
const float scale = 0.001;

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

    Planet Star;
    Star.mass = 90000000;
    Star.radius = 100;
    Star.pos = {960, 540};
    Star.color = ORANGE;

    Planet Planet;
    Planet.mass = 1000;
    Planet.radius = 40;
    Planet.pos = {5000, 540};
    Planet.color = BLUE;

    AddPhysics(&Star);
    AddPhysics(&Planet);

    float planetSpeed = circOrbit(gravConst, Star, Planet);

    Planet.vel = {0, planetSpeed};

    while (!WindowShouldClose())
    {
        float deltaTime = timeWarp * GetFrameTime();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouseChange = GetMouseDelta(); // Getting mouse delta for movement
            camera.target = Vector2Add(camera.target, Vector2Scale(mouseChange, -1.0f / camera.zoom)); // Uses the mouse delta to move the camera in the direciton of movement
        }
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f)); // Uses log for consistent mouse wheel zooming


        if (IsKeyPressed(KEY_PERIOD) && timeWarp < 12) timeWarp += 1;
        if (IsKeyPressed(KEY_COMMA) && timeWarp > 0) timeWarp -= 1;

        ProcessPhysics(gravConst, deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);
            BeginMode2D(camera);

            showOrbits(gravConst, deltaTime);

            Star.render();
            Planet.render();

            EndMode2D();
            
            std::string text = std::to_string(timeWarp);
            DrawText(text.c_str(), 10, 40, 32, WHITE);

        EndDrawing();
    }

    return 0;
}