#pragma once
#include <SFML/Graphics.hpp>
#include "event_loop.h"

class Player : public EventListener {
public:
    sf::RectangleShape shape;
    Player();

    void onEvent(const sf::Event& event) override;
    void move();
};