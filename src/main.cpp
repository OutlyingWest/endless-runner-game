#include "ecs/registry.hpp"
#include "systems/physics_system.h"
#include "systems/render_system.h"
#include "systems/input_system.h"
#include "systems/gameplay_system.h"
#include "systems/collision_system.h"
#include "entities/player.h"
#include "entities/obstacles.h"
#include "components.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS SFML");
    window.setFramerateLimit(60);

    Registry registry;

    // === SYSTEMS ===
    PhysicsSystem physics(1000.f);
    InputSystem input(-200.f, 200.f, -600.f);
    RenderSystem render;
    GameplaySystem gameplay;
    CollisionSystem collision(500.f);

        
    Entity player = createPlayer(registry, 100.f, 500.f);
    Entity obstacle = createRectangleObstacle(registry, 800.f, 450.f, window.getSize().x);

    // === GAME LOOP ===
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        input.update(registry);
        physics.update(registry, dt);
        collision.update(registry);
        gameplay.update(registry);

        window.clear();
        render.update(registry, window);
        window.display();
    }

    return 0;
}
