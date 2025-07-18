#pragma once
#include "dispatchers/collision_event.h"
#include <vector>

class CollisionEventDispatcher {
public:
    void subscribe(ICollisionListener* listener) {
        listeners.push_back(listener);
    }

    void notify(const CollisionEvent& event) {
        for (auto* listener : listeners) {
            listener->onCollision(event);
        }
    }

private:
    std::vector<ICollisionListener*> listeners;
};