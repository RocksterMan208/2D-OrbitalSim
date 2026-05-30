#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

constexpr int windowWidth = 1920;
constexpr int windowHeight = 1080;
const std::string windowTitle = "Epic Window";

const float gravConst = 100.0f;

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);

    Planet center;
    center.mass = 10000.0f;
    center.radius = 100.0f;
    center.pos = {960, 540};
    center.color = ORANGE;

    Planet satellite;
    satellite.mass = 3333.3f;
    satellite.radius = 20.0f;
    satellite.pos = {1140, 540};
    satellite.color = BLUE;

    //float speedCirc = sqrt(gravConst * center.mass / 300);
    float speedCirc = 90.0f;

    satellite.vel = {0, -speedCirc};

    while (!WindowShouldClose())
    {
        satellite.update(gravConst, center);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        center.render();
        satellite.render();

        EndDrawing();
    }

    return 0;
}