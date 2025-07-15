#include "gameplay_system.h"

void GameplaySystem::update(std::vector<Entity*>& entities) {
    for (Entity* e : entities) {
        e->onGameplayUpdate();
    }
}