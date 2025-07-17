#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdint>

using Entity = std::uint32_t;

class Registry {
public:
    Entity createEntity() {
        Entity id = nextEntityId++;
        entities.insert(id);
        return id;
    }

    template <typename T>
    void addComponent(Entity e, const T& component) {
        getStorage<T>()[e] = component;
    }

    template <typename T>
    T& getComponent(Entity e) {
        return getStorage<T>().at(e);
    }

    template <typename T>
    bool hasComponent(Entity e) const {
        const auto& storage = getStorage<T>();
        return storage.find(e) != storage.end();
    }

    template <typename... Components>
    std::vector<Entity> view() const {
        std::vector<Entity> result;
        for (Entity e : entities) {
            if ((hasComponent<Components>(e) && ...)) {
                result.push_back(e);
            }
        }
        return result;
    }

private:
    Entity nextEntityId = 0;
    std::unordered_set<Entity> entities;

    template <typename T>
    static std::unordered_map<Entity, T>& getStorage() {
        static std::unordered_map<Entity, T> storage;
        return storage;
    }
};
