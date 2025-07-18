#include "ecs/registry.hpp"
#include "systems/physics_system.h"
#include "systems/render_system.h"
#include "systems/input_system.h"
#include "systems/gameplay_system.h"
#include "systems/collision_system.h"
#include "entities/player.h"
#include "entities/obstacles.h"
#include "components.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS SFML");
    window.setPosition(sf::Vector2i(100, 100));
    window.setFramerateLimit(60);

    Registry registry;
    CollisionEventDispatcher dispatcher;

    // === SYSTEMS ===
    PhysicsSystem physics(1000.f);
    InputSystem input(-200.f, 200.f, -600.f);
    RenderSystem render;
    GameplaySystem gameplay;
    CollisionSystem collision(dispatcher);

    // Subscribe systems to collision events
    dispatcher.subscribe(&gameplay);
        
    Entity player = createPlayer(registry, 100.f, 500.f);
    Entity rectangleObstacle = createRectangleObstacle(
        registry, 
        800.f, 
        450.f, 
        50.f, 
        50.f, 
        window.getSize().x
    );
    Entity triangleObstacle = createTriangleObstacle(registry, 800.f, 450.f, window.getSize().x);
    Entity ground = createGround(
        registry, 
        0.f, 
        500.f, 
        window.getSize().x, 
        1.f
    );

    std::cout << "Created player with ID: " << player << '\n';
    std::cout << "Created rectangle obstacle with ID: " << rectangleObstacle << '\n';
    std::cout << "Created triangle obstacle with ID: " << triangleObstacle << '\n';
    std::cout << "Created ground with ID: " << ground << std::endl;

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
        gameplay.update(registry, dt);

        window.clear();
        render.update(registry, window);
        window.display();
    }

    return 0;
}
