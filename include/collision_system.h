#pragma once
#include <vector>
#include "entity.h"

class CollisionSystem {
public:
    void update(std::vector<Entity*>& entities);
};