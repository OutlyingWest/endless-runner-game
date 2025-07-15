#pragma once
#include "entity.h"
#include <vector>

class PhysicsSystem {
public:
    explicit PhysicsSystem(float gravityValue);
    void update(std::vector<Entity*>& entities, float dt);

private:
    float gravity;
};