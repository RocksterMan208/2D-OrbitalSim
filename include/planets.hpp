#pragma once

#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <vector>

struct Planet
{
    private:

    std::vector<Vector2> positions;
    
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

        void showPrevOrbit()
        {   
            positions.push_back(pos);

            for (int  i = 1; i < positions.size(); i++)
            {
                Vector2 startPos = positions[i-1];
                Vector2 endPos = positions[i];

                DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, WHITE);
            }
        }

};

class PhysicsSystem
{
    private:
    std::vector<Planet*> planetList;
    public:

    void AddPhysics(Planet* target) {planetList.push_back(target);} 

    void ProcessPhysics(float gravConst, float dt)
    {
        std::vector<Vector2> acceleration(planetList.size(),{0,0});

        for (int i = 0; i < planetList.size(); i++)
        {
            Planet* object = planetList[i];
            Vector2 totalAccel = {0,0};

            for (int j = 0; j < planetList.size(); j++)
            {
                if (i == j) continue;

                Planet* other = planetList[j];

                Vector2 accel = object->getAcceleration(gravConst, *other);
                totalAccel = Vector2Add(totalAccel, accel);
            }

        acceleration[i] = totalAccel;
        }

        for (int i = 0; i < planetList.size(); i++)
        {
            planetList[i]->updateAndAcceleration(acceleration[i], dt);
        }
    }

    void showOrbits(float gravConst, float dt)
    {
        const int maxSteps = 20000;
        
        std::vector<Planet> future;

        for (Planet* planet : planetList) future.push_back(*planet);

        std::vector<Vector2> lastPos;

        for (Planet& planet : future) lastPos.push_back(planet.pos);

        for (int steps = 0; steps < maxSteps; steps++)
        {
            std::vector<Vector2> acceleration(future.size(), {0,0});

            for (int i = 0; i < future.size(); i++)
            {
                for (int j = 0; j < future.size(); j++)
                {
                    if (i == j) continue;

                    Vector2 accel = future[i].getAcceleration(gravConst, future[j]);
                    acceleration[i] = Vector2Add(acceleration[i], accel);
                }
            }

            for (int i = 0; i < future.size(); i++)
            {
                future[i].updateAndAcceleration(acceleration[i], dt);
                DrawLineV(lastPos[i], future[i].pos, WHITE);
                lastPos[i] = future[i].pos;
            }
        }
    }
};

inline PhysicsSystem physics;
inline void AddPhysics(Planet* target)
{
    physics.AddPhysics(target); // Adds physics calculations to the designated planet
}
inline void ProcessPhysics(float gravConst, float dt) // This is to be placed inside of the frame loop to calculate physics.
{
    physics.ProcessPhysics(gravConst, dt);
}

inline void showOrbits(float gravConst, float dt)
{
    physics.showOrbits(gravConst, dt);
}

inline float circOrbit(float gravConst, Planet center, Planet targetPlanet)
{
    return sqrt(gravConst * center.mass / Vector2Distance(center.pos, targetPlanet.pos));
}