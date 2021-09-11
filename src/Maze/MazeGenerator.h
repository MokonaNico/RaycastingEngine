//
// Created by mine- on 10-09-21.
//

#ifndef RAYCASTINGENGINE_MAZEGENERATOR_H
#define RAYCASTINGENGINE_MAZEGENERATOR_H

typedef struct {
    int x;
    int y;
} Cell;

void RandomDepthFirstSearch(int * maze, int w, int h);
void Rec_RandomDepthFirstSearch(int * maze, int w, int h, int x, int y);
void breakWalls(int * maze, int w, int h, int n);

#endif //RAYCASTINGENGINE_MAZEGENERATOR_H
