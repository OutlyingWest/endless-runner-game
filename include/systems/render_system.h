#pragma once
#include <SFML/Graphics.hpp>
#include "ecs/registry.hpp"

class RenderSystem {
public:
    void update(Registry& registry, sf::RenderWindow& window);
};