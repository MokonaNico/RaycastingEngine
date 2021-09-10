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

Vector inverse(Vector vector){
    Vector newVector;
    newVector.x = -vector.x;
    newVector.y = -vector.y;
    return newVector;
}

Vector dotProduct(Vector a, Vector b){
    Vector res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    return res;
}

double magnitude(Vector v){
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector normalize(Vector v){
    double m = magnitude(v);
    Vector res;
    res.x = v.x / m;
    res.y = v.y / m;
    return res;
}

Vector perpendicular(Vector v){
    Vector res;
    res.x = v.y;
    res.y = -v.x;
    return res;
}

Vector multiply(Vector v, double m){
    Vector res;
    res.x = v.x * m;
    res.y = v.y * m;
    return res;
}

double dist(Vector a, Vector b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}