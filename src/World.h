//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_WORLD_H
#define RAYCASTINGENGINE_WORLD_H

#include "LinearAlgebra.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

Vector pos;
Vector dir;
Vector plane;
int get_world_case(int x, int y);

#endif //RAYCASTINGENGINE_WORLD_H
