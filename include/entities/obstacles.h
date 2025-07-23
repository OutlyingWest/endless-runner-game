#pragma once
#include "ecs/registry.hpp"
#include "components.h"
#include <SFML/Graphics.hpp>

using ObstacleComponents = std::tuple<Position, Velocity, Obstacle, Damage, Renderable, Collidable>;

Entity createGround(
    Registry& registry,
     float x, 
     float y, 
     float width, 
     float height
);
Entity createRectangleObstacle(
    Registry& registry, 
    float x,
    float y, 
    float width, 
    float height, 
    float windowWidth
);
Entity createTriangleObstacle(Registry& registry, float x, float y, float windowWidth, float base, float height);