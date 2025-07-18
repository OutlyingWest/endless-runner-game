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
    // TODO: Use fixed-size array or a more efficient structure
    // as the number of listeners is usually known and small
    std::vector<ICollisionListener*> listeners;
};