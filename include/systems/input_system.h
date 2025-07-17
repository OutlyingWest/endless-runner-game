#pragma once
#include "ecs/registry.hpp"

class InputSystem {
public:
    InputSystem(float moveLeft, float moveRight, float jump);

    void update(Registry& registry);

private:
    float moveLeftSpeed;
    float moveRightSpeed;
    float jumpSpeed;
    void horizontalMovementUpdate(struct Velocity& vel);
    void jumpUpdate(struct Velocity& vel);
};