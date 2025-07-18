#pragma once
#include "ecs/registry.hpp"
#include "components.h"
#include "dispatchers/collision_event_dispatcher.h"

class CollisionSystem {
public:
    CollisionSystem(CollisionEventDispatcher& dispatcher);
    void update(Registry& registry);

private:
    CollisionEventDispatcher& collisionDispatcher;

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