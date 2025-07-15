#include "physics_system.h"

PhysicsSystem::PhysicsSystem(float gravityValue) : gravity(gravityValue) {}

void PhysicsSystem::update(std::vector<Entity*>& entities, float dt) {
    for (Entity* e : entities) {
        e->onGravityUpdate(dt, gravity);
        e->position += e->velocity * dt;
        e->updateShapePosition();
    };
}
