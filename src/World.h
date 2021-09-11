//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_WORLD_H
#define RAYCASTINGENGINE_WORLD_H

#include "LinearAlgebra.h"

#define MAX_SPRITE 128

typedef struct {
    Vector pos;
    int texture;
} Sprite;

Sprite sprites[MAX_SPRITE];
int sprite_length;

Vector pos;
Vector dir;
Vector plane;
int getWorldCase(int x, int y);
void loadWorld(char * file, int w, int h);
void setPlayer(double pos_x, double pos_y, double dir_x, double dir_y);
void setPlayerSpeed(double _mov, double _rot);
void addSprite(double _x, double _y, int _texture);
void closeWorld();
void setWorld(int * world, int w, int h);
#endif //RAYCASTINGENGINE_WORLD_H
