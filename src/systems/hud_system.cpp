#include "systems/hud_system.h"
#include "components.h"
#include <iostream>

HudSystem::HudSystem() {
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Failed to load HUD font!" << std::endl;
    }
}

void HudSystem::update(Registry& registry, sf::RenderWindow& window) {
    for (Entity e : registry.view<PlayerControlled, Health>()) {
        const auto& hp = registry.getComponent<Health>(e);
        drawHealthBar(window, hp.current, hp.max);
        drawHealthText(window, hp.current, hp.max);
    }
}

void HudSystem::drawHealthBar(sf::RenderWindow& window, int currentHp, int maxHp) {
    float pct = static_cast<float>(currentHp) / maxHp;

    // Background
    sf::RectangleShape background(sf::Vector2f(120.f, 16.f));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setPosition(10.f, 10.f);
    window.draw(background);

    // Foreground
    sf::RectangleShape bar(sf::Vector2f(120.f * pct, 16.f));
    bar.setFillColor(sf::Color::Green);
    bar.setPosition(10.f, 10.f);
    window.draw(bar);
}

void HudSystem::drawHealthText(sf::RenderWindow& window, int currentHp, int maxHp) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(14.f, 10.f);
    text.setString("HP: " + std::to_string(currentHp) + " / " + std::to_string(maxHp));
    window.draw(text);
}