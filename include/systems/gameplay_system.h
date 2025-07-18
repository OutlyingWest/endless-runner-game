#pragma once
#include "ecs/registry.hpp"
#include "dispatchers/collision_event.h"

class GameplaySystem : public ICollisionListener {
public:
    void update(Registry& registry, float dt);
    void onCollision(const CollisionEvent& event) override;

private:
    Registry* registryPtr = nullptr;
    void updateInvincible(Registry& registry, Entity e, float dt);
    void applyPlayerDamageOnCollision(const CollisionEvent& event);
    void addPlayerShakingOnObstacleCollision(const CollisionEvent& event);

};