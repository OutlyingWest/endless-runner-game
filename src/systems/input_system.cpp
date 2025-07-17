#include <SFML/Window/Keyboard.hpp>
#include "systems/input_system.h"
#include "components.h"
#include <iostream>


InputSystem::InputSystem(
    float left,
    float right,
    float jump
):
    moveLeftSpeed(left),
    moveRightSpeed(right),
    jumpSpeed(jump),
    doubleJumpSpeed(jump / 1.2) {}

void InputSystem::update(Registry& registry) {
    for (Entity e : registry.view<PlayerControlled, Velocity>()) {
        auto& vel = registry.getComponent<Velocity>(e);
        horizontalMovementUpdate(vel);
        jumpUpdate(registry, e, vel);
    }
}

void InputSystem::horizontalMovementUpdate(Velocity& vel) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        vel.x = moveLeftSpeed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        vel.x = moveRightSpeed;
    } else {
        vel.x = 0.f;
    }
}

void InputSystem::jumpUpdate(Registry& registry, Entity e, Velocity& vel) {
    bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                       sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (jumpPressed && !wasJumpPressed) {
        if (registry.hasComponent<OnGround>(e)) {
            vel.y = jumpSpeed;
            jumpCount = 1;
            registry.removeComponent<OnGround>(e);
            std::cout << "Player jumped from ground!" << std::endl;
        }
        else if (jumpCount < 2) {
            vel.y = doubleJumpSpeed;
            jumpCount++;
            std::cout << "Player jumped in air!" << std::endl;
        }
    }
    wasJumpPressed = jumpPressed;
}
