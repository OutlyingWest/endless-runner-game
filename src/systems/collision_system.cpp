#include "systems/collision_system.h"
#include <variant>
#include <vector>
#include <cmath>
#include <SFML/System/Vector2.hpp>


CollisionSystem::CollisionSystem(float groundY) : groundY(groundY) {}

void CollisionSystem::update(Registry& registry) {
    for (Entity e : registry.view<Position, Collidable>()) {
        entityToOthersCollisionUpdate(registry, e);
        groundCollisionUpdate(registry, e);

    }
}

void CollisionSystem::entityToOthersCollisionUpdate(Registry& registry, Entity a) {
    auto& positionA = registry.getComponent<Position>(a);
    auto& collidableA = registry.getComponent<Collidable>(a);

    sf::Vector2f positionA2f(positionA.x, positionA.y);
    auto polygonA = getPoints(collidableA.collider, positionA2f);

    for (Entity b : registry.view<Position, Collidable>()) {
        if (a == b) continue;

        auto& positionB = registry.getComponent<Position>(b);
        auto& collidableB = registry.getComponent<Collidable>(b);

        sf::Vector2f positionB2f(positionB.x, positionB.y);
        auto polygonB = getPoints(collidableB.collider, positionB2f);

        if (polygonsIntersect(polygonA, polygonB)) {
            if (!registry.hasComponent<Collided>(a)) {
                registry.addComponent(a, Collided{b});
            }
        }
    }
}

void CollisionSystem::groundCollisionUpdate(Registry& registry, Entity e) {
    auto& position = registry.getComponent<Position>(e);
    auto& velocity = registry.getComponent<Velocity>(e);
    auto& renderable = registry.getComponent<Renderable>(e);

    float height = renderable.shape->getGlobalBounds().height;

    if (position.y + height >= groundY) {
        position.y = groundY - height; // Reset position to ground level
        velocity.y = 0.f; // Reset vertical velocity
        if (!registry.hasComponent<Collided>(e)) {
            registry.addComponent(e, Collided{GROUND_ENTITY});
        }
    }
}

inline std::vector<sf::Vector2f> CollisionSystem::getPoints(
    const ColliderVariant& col,
    const sf::Vector2f& pos
) {
    return std::visit([&](const auto& c) -> std::vector<sf::Vector2f> {
        using T = std::decay_t<decltype(c)>;
        if constexpr (std::is_same_v<T, RectangleCollider>) {
            return {
                {pos.x, pos.y},
                {pos.x + c.width, pos.y},
                {pos.x + c.width, pos.y + c.height},
                {pos.x, pos.y + c.height}
            };
        } else if constexpr (std::is_same_v<T, TriangleCollider>) {
            return {
                c.p1 + pos,
                c.p2 + pos,
                c.p3 + pos
            };
        }
    }, col);
}

// Separating Axis Theorem
inline bool polygonsIntersect(
    const std::vector<sf::Vector2f>& a,
    const std::vector<sf::Vector2f>& b
) {
    auto getAxes = [](const std::vector<sf::Vector2f>& poly) {
        std::vector<sf::Vector2f> axes;
        size_t n = poly.size();
        for (size_t i = 0; i < n; ++i) {
            sf::Vector2f edge = poly[(i + 1) % n] - poly[i];
            sf::Vector2f normal(-edge.y, edge.x);
            float len = std::sqrt(normal.x * normal.x + normal.y * normal.y);
            axes.push_back({normal.x / len, normal.y / len});
        }
        return axes;
    };

    auto project = [](const std::vector<sf::Vector2f>& poly, const sf::Vector2f& axis) {
        float min = axis.x * poly[0].x + axis.y * poly[0].y;
        float max = min;
        for (const auto& p : poly) {
            float proj = axis.x * p.x + axis.y * p.y;
            min = std::min(min, proj);
            max = std::max(max, proj);
        }
        return std::make_pair(min, max);
    };

    std::vector<sf::Vector2f> axes = getAxes(a);
    std::vector<sf::Vector2f> axesB = getAxes(b);
    axes.insert(axes.end(), axesB.begin(), axesB.end());

    for (const auto& axis : axes) {
        auto [minA, maxA] = project(a, axis);
        auto [minB, maxB] = project(b, axis);
        if (maxA < minB || maxB < minA)
            return false;
    }
    return true;
}