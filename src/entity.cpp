#include "entity.h"

Entity::Entity(
    const sf::Vector2f& size,
    const sf::Vector2f& pos,
    const sf::Vector2f& vel,
    const sf::Color& color,
    bool gravity,
    bool controlled
): 
    position(pos),
    velocity(vel),
    isGravityAffected(gravity),
    isPlayerControlled(controlled) {
    shape.setSize(size);
    shape.setFillColor(color);
    shape.setPosition(position);
}

void Entity::updateShapePosition() {
    shape.setPosition(position);
}

void Entity::onGameplayUpdate() {}


Obstacle::Obstacle(
    const sf::Vector2f& size,
    const sf::Vector2f& pos,
    const sf::Vector2f& vel,
    const sf::Color& color,
    float windowWidth
):
    Entity(size, pos, vel, color, false, false),
    windowWidth(windowWidth){}

// Override the onGameplayUpdate method for Obstacle
// to handle its specific behavior, such as resetting position when it goes off-screen
void Obstacle::onGameplayUpdate() {
    if (position.x + shape.getSize().x < 0) {
        position.x = windowWidth;
        updateShapePosition();
    }
}
