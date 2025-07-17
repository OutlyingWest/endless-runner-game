#pragma once
#include <variant>
#include <SFML/Graphics.hpp>

struct Position {
    float x, y;
};

struct Velocity {
    float x, y;
};

struct PlayerControlled {};

struct GravityAffected {};

struct Enemy {};

struct Ground {};

struct OnGround {};

struct Collided {
    Entity other;
};

struct Renderable {
    std::unique_ptr<sf::Shape> shape;

    Renderable() = default;
    Renderable(std::unique_ptr<sf::Shape> s) : shape(std::move(s)) {}
    Renderable(Renderable&&) noexcept = default;
    Renderable& operator=(Renderable&&) noexcept = default;
    Renderable(const Renderable&) = delete;
    Renderable& operator=(const Renderable&) = delete;
};

struct Obstacle {
    float windowWidth;
};

// --- Collider types ---
struct RectangleCollider {
    float width, height;
};

struct TriangleCollider {
    sf::Vector2f p1, p2, p3;
};

using ColliderVariant = std::variant<RectangleCollider, TriangleCollider>;

struct Collidable {
    ColliderVariant collider;
};
