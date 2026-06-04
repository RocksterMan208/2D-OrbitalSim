#include <iostream>
#include <string>
#include <cmath>

#include <emscripten/emscripten.h>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"
#include "settings.hpp"

int timeWarp = 1;

Camera2D camera = {0};

Planet Star;
Planet planet;
Planet moon;

void update()
{
    float deltaTime = timeWarp * GetFrameTime();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouseChange = GetMouseDelta();
        camera.target = Vector2Add(camera.target, Vector2Scale(mouseChange, -1.0f / camera.zoom));
    }

    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

    if (IsKeyPressed(KEY_PERIOD) && timeWarp < 12) timeWarp += 1;
    if (IsKeyPressed(KEY_COMMA) && timeWarp > 0) timeWarp -= 1;

    ProcessPhysics(gravConst, deltaTime);

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

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());

    camera.offset = {windowWidth / 2.0f, windowHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.target = {windowWidth / 2.0f, windowHeight / 2.0f};
    camera.zoom = 1.0f;

    Star.mass = 900000.0f;
    Star.radius = 100.0f;
    Star.pos = {960.0f, 540.0f};
    Star.color = ORANGE;

    planet.mass = 1000.0f;
    planet.radius = 30.0f;
    planet.pos = {5000.0f, 540.0f};
    planet.color = BLUE;

    moon.mass = 333.3f;
    moon.radius = 10.0f;
    moon.pos = {5100.0f, 540.0f};
    moon.color = DARKGRAY;

    AddPhysics(&moon);
    AddPhysics(&Star);
    AddPhysics(&planet);

    float planetSpeed = circOrbit(gravConst, Star, planet);
    float moonSpeed = circOrbit(gravConst, planet, moon);

    planet.vel = {0.0f, planetSpeed};
    moon.vel = {0.0f, moonSpeed + planetSpeed};

    emscripten_set_main_loop(update, 0, 1);

    return 0;
}