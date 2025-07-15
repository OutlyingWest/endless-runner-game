#include "input_system.h"
#include <SFML/Window/Keyboard.hpp>

void InputSystem::update(std::vector<Entity*>& entities) {
    for (Entity* entity : entities) {
        if (!entity->isPlayerControlled) continue;
        horizontalMovementUpdate(entity);
        jumpUpdate(entity);
    }
}

void InputSystem::horizontalMovementUpdate(Entity* entity) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        entity->velocity.x = -200.f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        entity->velocity.x = 200.f;
    } else {
        entity->velocity.x = 0.f;
    }
}

void InputSystem::jumpUpdate(Entity* entity) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (entity->velocity.y == 0) {
            entity->velocity.y = -600.f;
        }
    }
}