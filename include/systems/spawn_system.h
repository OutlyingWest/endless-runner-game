#pragma once
#include "ecs/registry.hpp"

class SpawnSystem {
public:
    SpawnSystem(float screenWidth, float screenHeight, float groundY);

    void update(Registry& registry, float dt);

private:
    float screenWidth;
    float screenHeight;
    float groundY; // Y position of the ground

    float elapsedTime = 0.f;

    // Timers for each type
    float rectangleTimer = 0.f;
    float triangleTimer = 0.f;
    float doubleTimer = 0.f;

    // Intervals (will decrease with time to increase difficulty)
    float rectangleInterval = 45.f;
    float triangleInterval = 70.f;
    float doubleInterval = 80.f;

    void trySpawnRectangle(Registry& registry);
    void trySpawnTriangle(Registry& registry);
    void trySpawnDouble(Registry& registry);

    float randomFloat(float min, float max);
};