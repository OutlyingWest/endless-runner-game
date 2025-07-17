#include "systems/collision_system.h"
#include "components.h"

CollisionSystem::CollisionSystem(float groundY) : groundY(groundY) {}

void CollisionSystem::update(Registry& registry) {
    for (Entity e : registry.view<Position, Velocity>()) {
        auto& pos = registry.getComponent<Position>(e);
        auto& vel = registry.getComponent<Velocity>(e);

        float bottom = pos.y + 50.f;
        if (bottom >= groundY) {
            pos.y = groundY - 50.f;
            vel.y = 0.f;
        }
    }
}