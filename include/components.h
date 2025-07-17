#pragma once
#include <SFML/Graphics.hpp>

struct Position {
    float x, y;
};

struct Velocity {
    float x, y;
};

struct PlayerControlled {};

struct GravityAffected {};

struct Renderable {
    sf::RectangleShape shape;
};

struct Obstacle {
    float windowWidth;
};