#include <SFML/Window/Keyboard.hpp>
#include "systems/input_system.h"
#include "components.h"


InputSystem::InputSystem(
    float left,
    float right,
    float jump
):
    moveLeftSpeed(left),
    moveRightSpeed(right),
    jumpSpeed(jump) {}

void InputSystem::update(Registry& registry) {
    for (Entity e : registry.view<PlayerControlled, Velocity>()) {
        auto& vel = registry.getComponent<Velocity>(e);
        horizontalMovementUpdate(vel);
        jumpUpdate(vel);
    }
}

void InputSystem::horizontalMovementUpdate(struct Velocity& vel) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x = moveLeftSpeed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x = moveRightSpeed;
    } else {
        vel.x = 0.f;
    }
}

void InputSystem::jumpUpdate(struct Velocity& vel) {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) &&
        vel.y == 0.f) {
        vel.y = jumpSpeed;
    }
}
