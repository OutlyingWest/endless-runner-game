#pragma once
#include "ecs/registry.hpp"
#include "components.h"
#include <SFML/Graphics.hpp>

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
Entity createTriangleObstacle(Registry& registry, float x, float y, float windowWidth);