#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool isGravityAffected;
    bool isPlayerControlled;

    Entity(
        const sf::Vector2f& size,
        const sf::Vector2f& pos,
        const sf::Vector2f& vel,
        const sf::Color& color,
        bool gravity,
        bool controlled
    );
    virtual ~Entity() = default;
    virtual void onGameplayUpdate(); 
    virtual void updateShapePosition();
    virtual void onGravityUpdate(float dt, float gravity);
};


class Obstacle : public Entity {
public:
    float windowWidth;
    
    Obstacle(
        const sf::Vector2f& size,
        const sf::Vector2f& pos,
        const sf::Vector2f& vel,
        const sf::Color& color,
        float windowWidth
    );

    void onGameplayUpdate() override;
    void onGravityUpdate(float dt, float gravity) override;
};
