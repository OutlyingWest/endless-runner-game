#include "systems/gameplay_system.h"
#include "components.h"
#include <iostream>

void GameplaySystem::update(Registry& registry, float dt) {
    // Update the internal registry pointer to use it in onCollision callback
    registryPtr = &registry; 

    for (Entity e : registry.view<Obstacle, Position>()) {
        auto& pos = registry.getComponent<Position>(e);
        auto& obs = registry.getComponent<Obstacle>(e);

        // If the obstacle is off-screen
        if (pos.x + 50.f < 0.f) {  
            pos.x = obs.windowWidth;
        }
    }
    for (Entity e : registry.view<Invincible>()) {
        updateInvincible(registry, e, dt);
    }

}

void GameplaySystem::updateInvincible(Registry& registry, Entity e, float dt) {
    auto& inv = registry.getComponent<Invincible>(e);
    inv.elapsed += dt;

    if (inv.elapsed >= inv.duration) {
        registry.removeComponent<Invincible>(e);
        std::cout << "Entity " << e << " is no longer invincible." << std::endl;
    }
}



void GameplaySystem::onCollision(const CollisionEvent& event) {
    if (!registryPtr) return;

    applyPlayerDamageOnCollision(event);
    addPlayerShakingOnObstacleCollision(event);
}

void GameplaySystem::applyPlayerDamageOnCollision(const CollisionEvent& event) {
    if (!registryPtr->hasComponent<PlayerControlled>(event.entityA)) {
        return;
    }

    Entity player = event.entityA;
    Entity other = event.entityB;

    if (registryPtr->hasComponent<Invincible>(player)) {
        return;
    }

    if (registryPtr->hasComponent<Damage>(other)) {
        int dmg = registryPtr->getComponent<Damage>(other).amount;

        auto& hp = registryPtr->getComponent<Health>(player);
        hp.current = std::max(0, hp.current - dmg);
        registryPtr->addComponent(player, Invincible{1.0f, 0.f});

        std::cout << "Player took " << dmg << " damage! " << "hp: " << hp.current << '\n';
    }
}

// Check if the player collided with an obstacle or ground and add shaking effect
void GameplaySystem::addPlayerShakingOnObstacleCollision(const CollisionEvent& event) {
    if (!registryPtr->hasComponent<PlayerControlled>(event.entityA)) {
        return;
    }
    Entity player = event.entityA;
    Entity other = event.entityB;
    if (registryPtr->hasComponent<Obstacle>(other)) {
        if (!registryPtr->hasComponent<Shaking>(player)) {
            // Shake for 0.3s with magnitude 7
            registryPtr->addComponent(player, Shaking{0.3f, 0.f, 7.f});
        }
    }
}