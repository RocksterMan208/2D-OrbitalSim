#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

#include "settings.hpp"

int timeWarp = 1;

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(targFPS);

    Camera2D camera = {0};
    camera.offset = {windowWidth/2, windowHeight/2};
    camera.rotation = 0;
    camera.target = {windowWidth/2, windowHeight/2};
    camera.zoom = 1.0f;

    Planet Star;
    Star.mass = 900000.0f;
    Star.radius = 100.0f;
    Star.pos = {960, 540};
    Star.color = ORANGE;

    Planet planet;
    planet.mass = 1000.0f;
    planet.radius = 30.0f;
    planet.pos = {5000, 540};
    planet.color = BLUE;

    Planet moon;
    moon.mass = 333.3f;
    moon.radius = 10.0f;
    moon.pos = {5100, 540};
    moon.color = DARKGRAY;

    AddPhysics(&moon);
    AddPhysics(&Star);
    AddPhysics(&planet);

    float planetSpeed = circOrbit(gravConst, Star, planet);
    float moonSpeed = circOrbit(gravConst, planet, moon);

    planet.vel = {0, planetSpeed};
    moon.vel = {0, moonSpeed+planetSpeed};

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

        camera.target = moon.pos;

        BeginDrawing();
        ClearBackground(BLACK);
            BeginMode2D(camera);

            showOrbits(gravConst, deltaTime);

            Star.render();
            planet.render();
            moon.render();

            EndMode2D();
            
            std::string text = std::to_string(timeWarp);
            DrawText(text.c_str(), 10, 40, 32, WHITE);

        EndDrawing();
    }

    return 0;
}