#include "systems/gameplay_system.h"
#include "components.h"
#include <iostream>

void GameplaySystem::update(Registry& registry) {
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
}

void GameplaySystem::onCollision(const CollisionEvent& event) {
    if (!registryPtr) return;

    if (registryPtr->hasComponent<PlayerControlled>(event.entityA)) {
        Entity player = event.entityA;
        std::cout << "Player collided with: " << event.entityB << std::endl;
        
        // Check if the player collided with an obstacle or ground and apply shaking effect
        if (registryPtr->hasComponent<Obstacle>(event.entityB)) {
            if (!registryPtr->hasComponent<Shaking>(player)) {
                registryPtr->addComponent(player, Shaking{0.3f, 0.f, 7.f}); // Shake for 0.3s with magnitude 7
            }
        } else if (registryPtr->hasComponent<Ground>(event.entityB)) {
            // Player landed on the ground
        }
    }
}