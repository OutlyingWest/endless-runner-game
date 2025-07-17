#pragma once
#include "ecs/registry.hpp"

class GameplaySystem {
public:
    void update(Registry& registry);
};