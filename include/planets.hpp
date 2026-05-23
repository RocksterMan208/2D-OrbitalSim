#pragma once

#include "raylib.h"
#include "raymath.h"

#include <iostream>

struct Planet
{
    public:
        Vector2 pos;
        float planetRad;
        double planetWeight;
        Color planetColor;
        float orbitRad;
        Vector2 orbitCent;

        float angle = 0;

        void update(double gravConstant)
        {
            
            pos.x = orbitCent.x + orbitRad * cos(angle);
            pos.y = orbitCent.y + orbitRad * sin(angle);

            std::cout << pos.x << " | " << pos.y << std::endl;

            angle += .1 * DEG2RAD;
        }

        void render()
        {
            DrawCircle(pos.x, pos.y, planetRad, planetColor);
        }
};