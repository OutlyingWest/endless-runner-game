#pragma once
#include "ecs/registry.hpp"

class PhysicsSystem {
public:
    PhysicsSystem(float gravity);
    void update(Registry& registry, float dt);

private:
    float gravity;

    void applyGravity(Registry& registry, Entity e, float dt);
    void applyShaking(Registry& registry, Entity e, float dt);
};