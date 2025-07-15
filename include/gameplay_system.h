#pragma once
#include <vector>
#include "entity.h"

class GameplaySystem {
public:
    void update(std::vector<Entity*>& entities);
};