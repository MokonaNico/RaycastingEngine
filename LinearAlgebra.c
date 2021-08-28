//
// Created by mine- on 28-08-21.
//

#include <math.h>
#include "LinearAlgebra.h"

Vector rotate(Vector vector, double angle){
    Vector newVector;
    newVector.x = vector.x * cos(angle) - vector.y * sin(angle);
    newVector.y = vector.x * sin(angle) + vector.y * cos(angle);
    return newVector;
}