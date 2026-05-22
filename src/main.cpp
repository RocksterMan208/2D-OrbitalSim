#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
const std::string windowTitle = "Epic Window";

constexpr float pixelScale = 1281.33f;
const double gravConst = 6.674e-11;

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);

    Planet test;
    test.pos = {400,300};
    test.planetRad = 80;
    test.planetColor = RED;
    test.planetWeight = 5.9722e24;

    Planet test2;
    test2.pos = {100,300};
    test2.planetRad = 40;
    test2.planetColor = RED;
    test2.planetWeight = 7.35e22;

    while (!WindowShouldClose())
    {
        test.update(gravConst, test2);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        test.render();
        test2.render();

        EndDrawing();
    }

    return 0;
}