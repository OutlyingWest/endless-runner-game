#include "systems/render_system.h"
#include "components.h"

void RenderSystem::update(Registry& registry, sf::RenderWindow& window) {
    for (Entity e : registry.view<Position, Renderable>()) {
        auto& pos = registry.getComponent<Position>(e);
        auto& rend = registry.getComponent<Renderable>(e);

        rend.shape.setPosition(pos.x, pos.y);
        window.draw(rend.shape);
    }
}