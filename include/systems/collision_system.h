#pragma once
#include "ecs/registry.hpp"

class CollisionSystem {
public:
    CollisionSystem(float groundY);
    void update(Registry& registry);

private:
    float groundY;
};