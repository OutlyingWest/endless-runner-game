#pragma once
#include "entity.h"
#include <vector>

class InputSystem {
public:
    void update(std::vector<Entity*>& entities);

private:
    void horizontalMovementUpdate(Entity* entity);
    void jumpUpdate(Entity* entity);
};