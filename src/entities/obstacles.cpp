#include "entities/obstacles.h"

Entity createGround(
    Registry& registry,
     float x, 
     float y, 
     float width, 
     float height
) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Ground{});

    auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    shape->setFillColor(sf::Color::White);
    registry.addComponent(e, Renderable{std::move(shape)});
    registry.addComponent(e, Collidable{RectangleCollider{width, height}});

    return e;
}

Entity createRectangleObstacle(
    Registry& registry, 
    float x,
    float y, 
    float width, 
    float height, 
    float windowWidth
) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{-100.f, 0.f});
    registry.addComponent(e, Obstacle{windowWidth});
    registry.addComponent(e, Damage{5});

    auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
    shape->setFillColor(sf::Color::Red);
    registry.addComponent(e, Renderable{std::move(shape)});
    registry.addComponent(e, Collidable{RectangleCollider{width, height}});

    return e;
}

Entity createTriangleObstacle(Registry& registry, float x, float y, float windowWidth, float base, float height) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{-120.f, 0.f});
    registry.addComponent(e, Obstacle{windowWidth});
    registry.addComponent(e, Damage{10});

    
    // Create a triangle shape
    auto triangle = std::make_unique<sf::ConvexShape>();
    triangle->setPointCount(3);
    triangle->setPoint(0, {0.f, base});
    triangle->setPoint(1, {height/2, 0.f});
    triangle->setPoint(2, {base, base});
    triangle->setFillColor(sf::Color::Blue);

    registry.addComponent(e, Renderable{std::move(triangle)});
    registry.addComponent(e, Collidable{
        TriangleCollider{
            {0.f, base},
            {height/2, 0.f},
            {base, base}
        }
    });

    return e;
}