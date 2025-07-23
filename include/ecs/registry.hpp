#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdint>
#include "components.h"

using Entity = std::uint32_t;

class Registry {
public:
    Entity createEntity() {
        Entity id = nextEntityId++;
        entities.insert(id);
        return id;
    }

    template<typename T>
    void addComponent(Entity e, T&& component) {
        getStorage<std::decay_t<T>>()[e] = std::forward<T>(component);
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

    template<typename T>
    void removeComponent(Entity e) {
        auto& storage = getStorage<T>();
        if (storage.find(e) != storage.end()) {
            storage.erase(e);
        }
    }

    template<typename Tuple>
    void destroyEntity(Entity e) {
        destroyEntityFromTuple<Tuple>(e, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
    }

private:
    Entity nextEntityId = 0;
    std::unordered_set<Entity> entities;

    template <typename T>
    static std::unordered_map<Entity, T>& getStorage() {
        static std::unordered_map<Entity, T> storage;
        return storage;
    }

    template<typename Tuple, std::size_t... I>
    void destroyEntityFromTuple(Entity e, std::index_sequence<I...>) {
        destroyEntity<std::tuple_element_t<I, Tuple>...>(e);
    }
};
