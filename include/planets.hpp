#pragma once

#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <vector>

struct Planet
{
    public:
        Vector2 pos;
        float mass;
        float radius;
        Color color;
        Vector2 vel;

        void update(float gravConstant, Planet center, float deltaTime)
        {
            
            Vector2 dir = Vector2Subtract(center.pos, pos);
            float distance = Vector2Length(dir);
            Vector2 normDir = Vector2Normalize(dir);

            float GAccel = gravConstant * center.mass / (distance*distance);
            Vector2 acceleration = Vector2Scale(normDir, GAccel);

            vel = Vector2Add(vel, Vector2Scale(acceleration, deltaTime));
            pos = Vector2Add(pos, Vector2Scale(vel, deltaTime));
        }

        void render()
        {
            DrawCircle(pos.x, pos.y, radius, color);
        }

        void drawPredictedOrbit(float gravConstant, Planet center) // PLEASE OPTIMIZE!!!!
        {
            const int maximumSteps = 6000; // Resolution of the line

            Planet future = *this; // Creating a copy of the satellite to orbit quickly then draw the path.

            Vector2 lastPos = future.pos; // For drawing the line
            Vector2 startPos = future.pos;

            for (int i = 0; i < maximumSteps; i++)
            {
                future.update(gravConstant, center, 1.0f/60.0f);
                DrawLineV(lastPos, future.pos, GRAY);

                lastPos = future.pos;
            }
        }
};