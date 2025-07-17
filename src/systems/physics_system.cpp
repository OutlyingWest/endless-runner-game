#include "systems/physics_system.h"
#include "components.h"

PhysicsSystem::PhysicsSystem(float gravity) : gravity(gravity) {}

void PhysicsSystem::update(Registry& registry, float dt) {
    for (Entity e : registry.view<Position, Velocity>()) {
        auto& pos = registry.getComponent<Position>(e);
        auto& vel = registry.getComponent<Velocity>(e);

        if (registry.hasComponent<GravityAffected>(e)) {
            vel.y += gravity * dt;
        }

        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
}
