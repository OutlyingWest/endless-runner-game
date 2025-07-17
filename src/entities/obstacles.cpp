#include "entities/obstacles.h"

Entity createRectangleObstacle(Registry& registry, float x, float y, float windowWidth) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{-100.f, 0.f});
    registry.addComponent(e, Obstacle{windowWidth});

    auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(50.f, 50.f));
    shape->setFillColor(sf::Color::Red);
    registry.addComponent(e, Renderable{std::move(shape)});
    registry.addComponent(e, Collidable{RectangleCollider{50.f, 50.f}});

    return e;
}

Entity createTriangleObstacle(Registry& registry, float x, float y, float windowWidth) {
    Entity e = registry.createEntity();

    registry.addComponent(e, Position{x, y});
    registry.addComponent(e, Velocity{-120.f, 0.f});
    registry.addComponent(e, Obstacle{windowWidth});

    
    // Create a triangle shape
    // The triangle will be an isosceles triangle
    const float base = 50.f;
    const float height = 50.f;

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