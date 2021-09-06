//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_LINEARALGEBRA_H
#define RAYCASTINGENGINE_LINEARALGEBRA_H

typedef struct {
    double x;
    double y;
} Vector;

Vector rotate(Vector vector, double angle);
Vector inverse(Vector vector);
Vector dotProduct(Vector a, Vector b);
double magnitude(Vector v);
Vector normalize(Vector v);
Vector perpendicular(Vector v);
Vector multiply(Vector v, double m);

#endif //RAYCASTINGENGINE_LINEARALGEBRA_H
