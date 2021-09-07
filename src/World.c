//
// Created by mine- on 28-08-21.
//

#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "World.h"
#include "EventHandler.h"

int * worldMap;

int worldWidth;
int worldHeight;

double movementSpeed = 5.0;
double rotationSpeed = 3.0;

Vector pos = {1.5,1.5};
Vector dir = {-1,0};
Vector plane = {0,0.66};

void setPlayer(double pos_x, double pos_y, double dir_x, double dir_y){
    pos.x = pos_x;
    pos.y = pos_y;
    Vector v = {dir_x, dir_y};
    dir = normalize(v);
    plane = multiply(perpendicular(dir),0.66);
}

void setPlayerSpeed(double _mov, double _rot){
    movementSpeed = _mov;
    rotationSpeed = _rot;
}

void load_world(char * file, int w, int h){
    worldWidth = w;
    worldHeight = h;
    FILE *in_file = fopen(file, "r");
    if(in_file == NULL){
        printf("Error ! Could not open the map file");
        return;
    }
    worldMap = malloc(sizeof(int) * w * h);
    int c;
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w+1; x++){
            c = fgetc(in_file);
            if(c != '\n' && c != EOF) {
                worldMap[x + y * w] = c - 48;
            }
        }
    }

    fclose(in_file);
}

int get_world_case(int x, int y){
    return worldMap[x + y * worldWidth];
}

void moveInADirection(Vector _dir, double move){
    if(get_world_case((int)(pos.x + _dir.x * move), (int)pos.y) == 0) pos.x += _dir.x * move;
    if(get_world_case((int)pos.x, (int)(pos.y+_dir.y*move)) == 0) pos.y += _dir.y * move;
}

void doMovements(double t){
    double move = t * movementSpeed;
    double rot = t * rotationSpeed;
    if(up_pressed){
        moveInADirection(dir, move);
    }
    if(down_pressed){
        moveInADirection(inverse(dir),move);
    }
    if(strafe_left_pressed){
        Vector left = rotate(dir, M_PI_2);
        moveInADirection(left, move);
    }
    if(strafe_right_pressed){
        Vector right = rotate(dir, -M_PI_2);
        moveInADirection(right, move);
    }
    if(left_pressed){
        dir = rotate(dir, rot);
        plane = rotate(plane, rot);
    }
    if(right_pressed){
        dir = rotate(dir, -rot);
        plane = rotate(plane, -rot);
    }
}

