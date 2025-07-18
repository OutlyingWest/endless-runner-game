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
    static int cnt = 0;
    for (Entity e : registry.view<PlayerControlled, Collided>()) {
        auto& collided = registry.getComponent<Collided>(e);
        std::cout << "Player collided: " << collided.other << "! "<< cnt++ << std::endl;
        registry.removeComponent<Collided>(e);
    }
}

void GameplaySystem::onCollision(const CollisionEvent& event) {
    if (!registryPtr) return;

    if (registryPtr->hasComponent<PlayerControlled>(event.entityA)) {
        std::cout << "Player collided with: " << event.entityB << std::endl;
    }
}