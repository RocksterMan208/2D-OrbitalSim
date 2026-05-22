#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;
const std::string windowTitle = "Epic Window";

constexpr int pixelScale = 100;
const double gravConst = 6.674e-11;

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);

    Planet test;
    test.pos = {400,300};
    test.planetRad = 80;
    test.planetColor = RED;

    Planet test2;
    test2.pos = {300,300};
    test2.planetRad = 40;
    test2.planetColor = RED;

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