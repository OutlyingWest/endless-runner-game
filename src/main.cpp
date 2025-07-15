#include <SFML/Graphics.hpp>
#include "physics_system.h"
#include "render_system.h"
#include "input_system.h"
#include "gameplay_system.h"
#include "collision_system.h"
#include "entity.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Template");
    window.setPosition(sf::Vector2i(200, 150));
    window.setFramerateLimit(120);

    PhysicsSystem physics(1000.f);
    RenderSystem renderer;
    InputSystem input;
    GameplaySystem gameplay;
    CollisionSystem collision;

    // === ENTITY CREATION ===
    Entity player(
        {50.f, 50.f},      // Size
        {100.f, 500.f},    // Initial position on the ground
        {0.f, 0.f},        // Initial velocity
        sf::Color::Green,  // Color
        true               // Player controlled
    );

    Obstacle obstacle(
        {50.f, 50.f},             
        {800.f, 450.f},           
        {-100.f, 0.f},            
        sf::Color::Red,           
        window.getSize().x         
    );

    std::vector<Entity*> entities = { &player, &obstacle };

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        input.update(entities);
        physics.update(entities, dt);
        collision.update(entities);
        gameplay.update(entities);

        // collision with ground
        if (player.position.y + player.shape.getSize().y >= 500.f) {
            player.position.y = 500.f - player.shape.getSize().y;
            player.velocity.y = 0;
            player.updateShapePosition();
        }

        window.clear();
        renderer.update(window, entities);
        window.display();
    }

    return 0;
}
