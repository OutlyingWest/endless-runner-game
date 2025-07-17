#include <SFML/Graphics.hpp>
#include "ecs/registry.hpp"
#include "systems/physics_system.h"
#include "systems/render_system.h"
#include "systems/input_system.h"
#include "systems/gameplay_system.h"
#include "systems/collision_system.h"
#include "components.h"

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

    // === PLAYER ENTITY ===
    Entity player = registry.createEntity();
    registry.addComponent(player, Position{100.f, 500.f});
    registry.addComponent(player, Velocity{0.f, 0.f});
    registry.addComponent(player, GravityAffected{});
    registry.addComponent(player, PlayerControlled{});

    sf::RectangleShape playerShape({50.f, 50.f});
    playerShape.setFillColor(sf::Color::Green);
    registry.addComponent(player, Renderable{playerShape});

    // === OBSTACLE ENTITY ===
    Entity obstacle = registry.createEntity();
    registry.addComponent(obstacle, Position{800.f, 450.f});
    registry.addComponent(obstacle, Velocity{-100.f, 0.f});
    registry.addComponent(obstacle, Obstacle{800.f});

    sf::RectangleShape obstacleShape({50.f, 50.f});
    obstacleShape.setFillColor(sf::Color::Red);
    registry.addComponent(obstacle, Renderable{obstacleShape});

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
