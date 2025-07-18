#pragma once
#include "ecs/registry.hpp"
#include "components.h"

class CollisionSystem {
public:
    void update(Registry& registry);

private:
    bool checkCollisionBetween(Registry& registry, Entity a, Entity b);
    void groundCollisionUpdate(
        Registry& registry,
        Entity a,
        Entity b
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