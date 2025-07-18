#pragma once
#include "ecs/registry.hpp"
#include "dispatchers/collision_event.h"

class GameplaySystem : public ICollisionListener {
public:
    void update(Registry& registry);
    void onCollision(const CollisionEvent& event) override;

private:
    Registry* registryPtr = nullptr;
};