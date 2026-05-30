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

        std::vector<Vector2> path;

        void update(float gravConstant, Planet center)
        {
            float dt = GetFrameTime();
            
            Vector2 dir = Vector2Subtract(center.pos, pos);
            float distance = Vector2Length(dir);
            Vector2 normDir = Vector2Normalize(dir);

            float GAccel = gravConstant * center.mass / (distance*distance);
            Vector2 acceleration = Vector2Scale(normDir, GAccel);

            vel = Vector2Add(vel, Vector2Scale(acceleration, dt));
            pos = Vector2Add(pos, Vector2Scale(vel, dt));
        }

        void render()
        {
            DrawCircle(pos.x, pos.y, radius, color);
        }
};