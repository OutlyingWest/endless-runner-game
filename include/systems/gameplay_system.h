#pragma once
#include "ecs/registry.hpp"
#include "dispatchers/collision_event.h"
// For window
#include <SFML/Graphics.hpp>

class GameplaySystem : public ICollisionListener {
public:
    void update(Registry& registry, float dt);
    void onCollision(const CollisionEvent& event) override;
    void setWindow(sf::RenderWindow* win) { window = win; }

private:
    Registry* registryPtr = nullptr;
    sf::RenderWindow* window = nullptr;

    void updateInvincible(Registry& registry, Entity e, float dt);
    void applyPlayerDamageOnCollision(const CollisionEvent& event);
    void addPlayerShakingOnObstacleCollision(const CollisionEvent& event);

};