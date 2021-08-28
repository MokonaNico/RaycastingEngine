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
#endif //RAYCASTINGENGINE_LINEARALGEBRA_H
