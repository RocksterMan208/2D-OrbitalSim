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
    center.mass = 100000.0f;
    center.radius = 100.0f;
    center.pos = {960, 540};
    center.color = ORANGE;

    Planet satellite;
    satellite.mass = 1000.0f;
    satellite.radius = 20.0f;
    satellite.pos = {1540, 540};
    satellite.color = BLUE;

    satellite.vel = {0.0f, 40.0f};

    Planet moon;
    moon.mass = 500.0f;
    moon.radius = 10.0f;
    moon.pos = {1600, 540};
    moon.color = DARKGRAY;

    float moonSpeed = 15;

    moon.vel = Vector2Add(satellite.vel, (Vector2){0.0f, -moonSpeed});


    while (!WindowShouldClose())
    {
        float deltaTime = timeWarp * GetFrameTime();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouseChange = GetMouseDelta(); // Getting mouse delta for movement
            camera.target = Vector2Add(camera.target, Vector2Scale(mouseChange, -1.0f / camera.zoom)); // Uses the mouse delta to move the camera in the direciton of movement
        }
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f)); // Uses log for consistent mouse wheel zooming

        if (IsKeyDown(KEY_UP)) satellite.vel.y -= 1.0f;
        if (IsKeyDown(KEY_DOWN)) satellite.vel.y += 1.0f;
        if (IsKeyDown(KEY_LEFT)) satellite.vel.x -= 1.0f;
        if (IsKeyDown(KEY_RIGHT)) satellite.vel.x += 1.0f;

        if (IsKeyPressed(KEY_PERIOD) && timeWarp < 4) timeWarp += 1;
        if (IsKeyPressed(KEY_COMMA) && timeWarp > 0) timeWarp -= 1;

        Vector2 satelliteAccel = satellite.getAcceleration(gravConst, center);

        Vector2 moonAccelSatellite = moon.getAcceleration(gravConst, satellite);
        Vector2 moonAccelCenter = moon.getAcceleration(gravConst, center);

        satellite.updateAndAcceleration(satelliteAccel, deltaTime);
        moon.updateAndAcceleration(Vector2Add(moonAccelCenter, moonAccelSatellite), deltaTime);

        std::cout << Vector2Distance(satellite.pos, moon.pos) << std::endl;

        BeginDrawing();
        ClearBackground(BLACK);
            BeginMode2D(camera);

            satellite.drawPredictedOrbit(gravConst, center);

            center.render();
            satellite.render();
            moon.render();

            EndMode2D();

            DrawFPS(10,10);
            
            std::string text = std::to_string(timeWarp);

            DrawText(text.c_str(), 10, 40, 16, BLACK);

        EndDrawing();
    }

    return 0;
}