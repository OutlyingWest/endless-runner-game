#pragma once
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <vector>

class RenderSystem {
public:
    void update(sf::RenderWindow& window, const std::vector<Entity*>& entities);
};