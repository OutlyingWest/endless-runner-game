#pragma once
#include "ecs/registry.hpp"
#include "components.h"
#include <SFML/Graphics.hpp>

Entity createRectangleObstacle(Registry& registry, float x, float y, float windowWidth);