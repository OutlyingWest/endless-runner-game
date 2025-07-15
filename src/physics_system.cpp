#include "physics_system.h"

PhysicsSystem::PhysicsSystem(float gravityValue) : gravity(gravityValue) {}

void PhysicsSystem::update(std::vector<Entity*>& entities, float dt) {
    for (Entity* e : entities) {
        if (e->isGravityAffected)
            e->velocity.y += gravity * dt;

        e->position += e->velocity * dt;
        e->updateShapePosition();
    }
}