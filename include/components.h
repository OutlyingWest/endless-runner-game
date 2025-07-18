#pragma once
#include <variant>
#include <SFML/Graphics.hpp>

// == Physics ==
struct Position {
    float x, y;
};

struct Velocity {
    float x, y;
};

struct OnGround {};

struct GravityAffected {};

// == Gameplay ==
struct PlayerControlled {};

struct Enemy {};

struct Ground {};

struct Obstacle {
    float windowWidth;
};

struct Health {
    int current;
    int max;
};

struct Damage {
    int amount;
};

struct Invincible {
    float duration; 
    float elapsed;
};

// == Collisions ==
// --- Collider types ---
struct RectangleCollider {
    float width, height;
};

struct TriangleCollider {
    sf::Vector2f p1, p2, p3;
};

using ColliderVariant = std::variant<RectangleCollider, TriangleCollider>;

// --- Collision components ---
struct Collidable {
    ColliderVariant collider;
};

// == Rendering ==
struct Renderable {
    std::unique_ptr<sf::Shape> shape;

    Renderable() = default;
    Renderable(std::unique_ptr<sf::Shape> s) : shape(std::move(s)) {}
    Renderable(Renderable&&) noexcept = default;
    Renderable& operator=(Renderable&&) noexcept = default;
    Renderable(const Renderable&) = delete;
    Renderable& operator=(const Renderable&) = delete;
};

// == Effects ==
struct Shaking {
    float duration;      // how long to shake
    float elapsed;       // how much time has passed
    float magnitude;     // how intense the shaking is
};
