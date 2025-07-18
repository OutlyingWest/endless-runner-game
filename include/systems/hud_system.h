#pragma once

#include <SFML/Graphics.hpp>
#include "ecs/registry.hpp"

class HudSystem {
public:
    HudSystem();

    void update(Registry& registry, sf::RenderWindow& window);

private:
    sf::Font font;

    void drawHealthBar(sf::RenderWindow& window, int currentHp, int maxHp);
    void drawHealthText(sf::RenderWindow& window, int currentHp, int maxHp);
};