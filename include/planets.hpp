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

        void update(double gravConstant, Planet otherPlanet)
        {
            Vector2 differencePos =  Vector2Subtract(pos, otherPlanet.pos);
            //std::cout << differencePos.x << " | " << differencePos.y << std::endl;
            float gravForce = gravConstant * (planetWeight * otherPlanet.planetWeight) / (differencePos.x + differencePos.y);

            std::cout << gravForce << std::endl;
        }

        void render()
        {
            DrawCircle(pos.x, pos.y, planetRad, planetColor);
        }
};