#include "systems/physics_system.h"
#include "components.h"

PhysicsSystem::PhysicsSystem(float gravity) : gravity(gravity) {}

void PhysicsSystem::update(Registry& registry, float dt) {
    for (Entity e : registry.view<Position, Velocity>()) {
        // Apply gravity
        auto& pos = registry.getComponent<Position>(e);
        auto& vel = registry.getComponent<Velocity>(e);

        if (registry.hasComponent<GravityAffected>(e)) {
            vel.y += gravity * dt;
        }

        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
    for (Entity e : registry.view<Shaking, Position>()) {
        // Apply shaking effect
        auto& shake = registry.getComponent<Shaking>(e);
        auto& pos = registry.getComponent<Position>(e);

        shake.elapsed += dt;
        if (shake.elapsed >= shake.duration) {
            registry.removeComponent<Shaking>(e);
            return;
        }

        float dx = ((std::rand() % 200) / 100.f - 1.f) * shake.magnitude;
        float dy = ((std::rand() % 200) / 100.f - 1.f) * shake.magnitude;
        pos.x += dx;
        pos.y += dy;
    }

}
