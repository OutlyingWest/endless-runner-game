#include "render_system.h"

void RenderSystem::update(sf::RenderWindow& window, const std::vector<Entity*>& entities) {
    for (const Entity* e : entities) {
        window.draw(e->shape);
    }
}