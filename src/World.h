//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_WORLD_H
#define RAYCASTINGENGINE_WORLD_H

#include "LinearAlgebra.h"

Vector pos;
Vector dir;
Vector plane;
int get_world_case(int x, int y);
void load_world(char * file, int w, int h);
void setPlayer(double pos_x, double pos_y, double dir_x, double dir_y);
void setPlayerSpeed(double _mov, double _rot);

#endif //RAYCASTINGENGINE_WORLD_H
