#include "systems/spawn_system.h"
#include "entities/obstacles.h"
#include "components.h"
#include <cstdlib>

SpawnSystem::SpawnSystem(float screenWidth, float screenHeight, float groundY)
    : screenWidth(screenWidth), screenHeight(screenHeight), groundY(groundY) {}

void SpawnSystem::update(Registry& registry, float dt) {
    elapsedTime += dt;

    // Increase difficulty every N seconds
    if (elapsedTime > 1000.f) {
        rectangleInterval = std::max(10.f, rectangleInterval - 0.2f);
        triangleInterval = std::max(10.f, triangleInterval - 0.3f);
        doubleInterval = std::max(10.f, doubleInterval - 0.5f);
        elapsedTime = 0.f;
    }

    rectangleTimer += dt;
    triangleTimer += dt;
    doubleTimer += dt;

    if (rectangleTimer >= rectangleInterval) {
        trySpawnRectangle(registry);
        rectangleTimer = 0.f;
    }
    if (triangleTimer >= triangleInterval) {
        trySpawnTriangle(registry);
        triangleTimer = 0.f;
    }
    if (doubleTimer >= doubleInterval) {
        trySpawnDouble(registry);
        doubleTimer = 0.f;
    }
}

float SpawnSystem::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

void SpawnSystem::trySpawnRectangle(Registry& registry) {
    float groundY = 500.f;
    float w = randomFloat(30.f, screenWidth / 4.f);
    float h = randomFloat(30.f, screenHeight / 2.f);
    float x = screenWidth;
    float y = groundY - h;  // stays on the ground
    createRectangleObstacle(registry, x, y, w, h, screenWidth);
}

void SpawnSystem::trySpawnTriangle(Registry& registry) {
    float groundY = 500.f;
    float base = randomFloat(30.f, screenWidth / 4.f);
    float height = randomFloat(30.f, screenHeight / 2.f);
    float x = screenWidth;
    float y = groundY - height;  // stays on the ground
    createTriangleObstacle(registry, x, y, screenWidth, base, height);
}

void SpawnSystem::trySpawnDouble(Registry& registry) {
    float groundY = 500.f;
    float gap = randomFloat(150.f, 200.f); // > 3 * player height (3*50=150)
    float topH = randomFloat(30.f, screenHeight / 2.f);
    float botH = randomFloat(30.f, screenHeight / 2.f);
    float base = randomFloat(30.f, screenWidth / 4.f);
    float x = screenWidth;

    // Top triangle (flipped)
    {
        Entity e = registry.createEntity();
        registry.addComponent(e, Position{x, 0.f});
        registry.addComponent(e, Velocity{-120.f, 0.f});
        registry.addComponent(e, Obstacle{screenWidth});

        auto shape = std::make_unique<sf::ConvexShape>();
        shape->setPointCount(3);
        shape->setPoint(0, sf::Vector2f(0.f, 0.f));
        shape->setPoint(1, sf::Vector2f(base / 2.f, topH));
        shape->setPoint(2, sf::Vector2f(base, 0.f));
        shape->setFillColor(sf::Color::Blue);
        registry.addComponent(e, Renderable{std::move(shape)});
        registry.addComponent(e, Collidable{TriangleCollider{{0.f, 0.f}, {base / 2.f, topH}, {base, 0.f}}});
    }

    // Bottom triangle (stays on the ground)
    float yBot = groundY - botH;
    createTriangleObstacle(registry, x, yBot, screenWidth, base, botH);
}
