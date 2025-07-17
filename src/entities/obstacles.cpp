#include "entities/obstacles.h"

Entity createRectangleObstacle(Registry& registry, float x, float y, float windowWidth) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{-100.f, 0.f});
    registry.addComponent(e, Obstacle{windowWidth});

    sf::RectangleShape shape({50.f, 50.f});
    shape.setFillColor(sf::Color::Red);
    registry.addComponent(e, Renderable{shape});

    return e;
}