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

        void render()
        {
            DrawCircle(pos.x, pos.y, radius, color);
        }

        void drawPredictedOrbit(float gravConstant, Planet center, float dt) // This currently does NOT work for a moon
        {
            const int maximumSteps = 10000; // Resolution of the line

            Planet future = *this; // Creating a copy of the satellite to orbit quickly then draw the path.

            Vector2 lastPos = future.pos; // For drawing the line

            for (int i = 0; i < maximumSteps; i++)
            {
                future.updateAndAcceleration(future.getAcceleration(gravConstant, center), dt);
                DrawLineV(lastPos, future.pos, GRAY);

                lastPos = future.pos;
            }
        }

        Vector2 getAcceleration(float gravConstant, Planet center) // Used for other calculations, typically for satellites of satellites (moons of planets).
        {
            Vector2 dir = Vector2Subtract(center.pos, pos);
            float distance = Vector2Length(dir);
            Vector2 normDir = Vector2Normalize(dir);

            float GAccel = gravConstant * center.mass / (distance*distance);

            return Vector2Scale(normDir, GAccel);
        }

        void updateAndAcceleration(Vector2 acceleration, float dt) // Use the acceleration gained from the getAcceleration function for acceleration
        {
            vel = Vector2Add(vel, Vector2Scale(acceleration, dt));
            pos = Vector2Add(pos, Vector2Scale(vel, dt));
        }
};

class PhysicsSystem
{
    private:
    std::vector<Planet*> planetList;
    public:

    void AddPhysics(Planet* target) {planetList.push_back(target);} // Adds physics calculations to the designated planet

    void ProcessPhysics(float gravConst, float dt, Planet center) // This is to be placed inside of the frame loop to calculate physics.
    {
        for (Planet* object : planetList )
        {
            Vector2 acc = object->getAcceleration(gravConst, center);
            object->updateAndAcceleration(acc, dt);
        }
    }
};