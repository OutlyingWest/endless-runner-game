#include "player.h"


#define PLAYER_SPEED 5.f


Player::Player() {
    shape.setSize({100.f, 100.f});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(350.f, 250.f);
}

void Player::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left)
            shape.setFillColor(sf::Color::Green);
        else if (event.mouseButton.button == sf::Mouse::Right)
            shape.setFillColor(sf::Color::Red);
    }
}

void Player::move() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            shape.move(-PLAYER_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            shape.move(PLAYER_SPEED, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            shape.move(0, -PLAYER_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            shape.move(0, PLAYER_SPEED);
        }
}