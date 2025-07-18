#include "entities/player.h"

Entity createPlayer(Registry& registry, float x, float y) {
    Entity e = registry.createEntity();

    // Basic components 
    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{0.f, 0.f});
    registry.addComponent(e, GravityAffected{});
    registry.addComponent(e, PlayerControlled{});
    registry.addComponent(e, Health{100, 100}); // Player starts with 100 health

    // Renderable component with a simple rectangle shape
    auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(50.f, 50.f));
    shape->setFillColor(sf::Color::Green);
    registry.addComponent(e, Renderable{std::move(shape)});
    registry.addComponent(e, Collidable{RectangleCollider{50.f, 50.f}});

    return e;
}