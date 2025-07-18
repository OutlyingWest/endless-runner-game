// Interface for collision events in a game engine
#pragma once
#include "ecs/registry.hpp"

struct CollisionEvent {
    Entity entityA;
    Entity entityB;
};

class ICollisionListener {
public:
    virtual ~ICollisionListener() = default;
    virtual void onCollision(const CollisionEvent& event) = 0;
};
