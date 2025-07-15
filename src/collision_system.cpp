#include "collision_system.h"

void CollisionSystem::update(std::vector<Entity*>& entities) {
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            Entity* a = entities[i];
            Entity* b = entities[j];

            if (a->shape.getGlobalBounds().intersects(b->shape.getGlobalBounds())) {
                a->onCollision(b);
                b->onCollision(a);
            }
        }
    }
}