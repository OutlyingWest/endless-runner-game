#pragma once
#include "entity.h"
#include <vector>

class InputSystem {
public:
    float moveBackSpeed;
    float moveForwardSpeed;
    float jumpSpeed;

    InputSystem(
        float moveBackSpeed,
        float moveForwardSpeed,
        float jumpSpeed
    );
    void update(std::vector<Entity*>& entities);

private:
    void horizontalMovementUpdate(Entity* entity);
    void jumpUpdate(Entity* entity);
};