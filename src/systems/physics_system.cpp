#include "systems/physics_system.h"
#include "components.h"

PhysicsSystem::PhysicsSystem(float gravity) : gravity(gravity) {}

void PhysicsSystem::update(Registry& registry, float dt) {
    for (Entity e : registry.view<Position, Velocity>()) {
        // Apply gravity
        auto& pos = registry.getComponent<Position>(e);
        auto& vel = registry.getComponent<Velocity>(e);

        // Section to insert physics logic
        applyGravity(registry, e, dt);
        applyShaking(registry, e, dt);

        // Update position based on velocity for all entities
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
}

void PhysicsSystem::applyGravity(Registry& registry, Entity e, float dt) {
    if (registry.hasComponent<GravityAffected>(e)) {
        auto& vel = registry.getComponent<Velocity>(e);
        vel.y += gravity * dt;
    }
}

void PhysicsSystem::applyShaking(Registry& registry, Entity e, float dt) {
    if (registry.hasComponent<Shaking>(e)) {
        auto& shake = registry.getComponent<Shaking>(e);
        shake.elapsed += dt;

        if (shake.elapsed >= shake.duration) {
            registry.removeComponent<Shaking>(e);
            return;
        }

        // Apply shaking effect
        auto& pos = registry.getComponent<Position>(e);
        float dx = ((std::rand() % 200) / 100.f - 1.f) * shake.magnitude;
        float dy = ((std::rand() % 200) / 100.f - 1.f) * shake.magnitude;
        pos.x += dx;
        pos.y += dy;
    }
}
