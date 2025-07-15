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