#include "systems/gameplay_system.h"
#include "components.h"

void GameplaySystem::update(Registry& registry) {
    for (Entity e : registry.view<Obstacle, Position, Velocity>()) {
        auto& pos = registry.getComponent<Position>(e);
        auto& obs = registry.getComponent<Obstacle>(e);

        // If the obstacle is off-screen
        if (pos.x + 50.f < 0.f) {  
            pos.x = obs.windowWidth;
        }
    }
}