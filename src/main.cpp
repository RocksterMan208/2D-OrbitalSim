#include <iostream>
#include <string>

#include "raylib.h"
#include "raymath.h"
#include "planets.hpp"

constexpr int windowWidth = 1920;
constexpr int windowHeight = 1080;
const std::string windowTitle = "Epic Window";

const double gravConst = 6.674e-11;

int main()
{
    InitWindow(windowWidth, windowHeight, windowTitle.c_str());
    SetTargetFPS(60);

    Planet test;
    test.planetRad = 100;
    test.planetColor = RED;
    test.pos.x = GetScreenWidth()/2;
    test.pos.y = GetScreenHeight()/2;

    Planet test2;
    test2.planetRad = 50;
    test2.planetColor = PURPLE;
    test2.pos.x = test.pos.x - 200;
    test2.pos.y = test.pos.y;
    test2.orbitCent = test.pos;
    test2.orbitRad = 400;

    while (!WindowShouldClose())
    {
        test2.update(gravConst);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        test.render();
        test2.render();

        EndDrawing();
    }

    return 0;
}