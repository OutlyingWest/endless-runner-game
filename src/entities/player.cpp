#include "entities/player.h"

Entity createPlayer(Registry& registry, float x, float y) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{0.f, 0.f});
    registry.addComponent(e, GravityAffected{});
    registry.addComponent(e, PlayerControlled{});

    sf::RectangleShape shape({50.f, 50.f});
    shape.setFillColor(sf::Color::Green);
    registry.addComponent(e, Renderable{shape});

    return e;
}