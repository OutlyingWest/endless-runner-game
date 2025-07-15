#include "entity.h"
#include <iostream>


Entity::Entity(
    const sf::Vector2f& size,
    const sf::Vector2f& pos,
    const sf::Vector2f& vel,
    const sf::Color& color,
    bool controlled
): 
    position(pos),
    velocity(vel),
    isPlayerControlled(controlled) {
    shape.setSize(size);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Entity::updateShapePosition() {
    shape.setPosition(position);
}

void Entity::onGameplayUpdate() {
    // Default gameplay update can be overridden by derived classes
}

void Entity::onGravityUpdate(float dt, float gravity) {
    velocity.y += gravity * dt;
}

void Entity::onCollision(Entity* other) {
    static int counter = 0;
    if (dynamic_cast<Obstacle*>(other)) {
        std::cout << "Jopa! " << counter++ << " \n";
    }
}


Obstacle::Obstacle(
    const sf::Vector2f& size,
    const sf::Vector2f& pos,
    const sf::Vector2f& vel,
    const sf::Color& color,
    float windowWidth
):
    Entity(size, pos, vel, color, false),
    windowWidth(windowWidth){}


// Reset position when Obstacle goes off-screen
void Obstacle::onGameplayUpdate() {
    if (position.x + shape.getSize().x < 0) {
        position.x = windowWidth;
        updateShapePosition();
    }
}

void Obstacle::onGravityUpdate(float dt, float gravity) {
    // Obstacles are not affected by gravity.
}
