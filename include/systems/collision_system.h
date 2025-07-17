#pragma once
#include "ecs/registry.hpp"
#include "components.h"

class CollisionSystem {
public:
    CollisionSystem(float groundY);
    void update(Registry& registry);

private:
    float groundY;
    void entityToOthersCollisionUpdate(Registry& registry, Entity a);
    void groundCollisionUpdate(
        Registry& registry,
        Entity a,
        Entity b,
        Position& positionA,
        Position& positionB
    );
    inline std::vector<sf::Vector2f> getPoints(
        const ColliderVariant& col,
        const sf::Vector2f& pos
    );
};

inline bool polygonsIntersect(
    const std::vector<sf::Vector2f>& a,
    const std::vector<sf::Vector2f>& b
);