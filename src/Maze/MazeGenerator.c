//
// Created by mine- on 10-09-21.
//

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "MazeGenerator.h"


Cell getRandomNeighbours(const int * maze, int w, int h, int x, int y){
    Cell poss_cell[4];
    int size = 0;
    if(x != 1 && maze[y * w + (x-2)] != -1){
        poss_cell[size].x = x-2;
        poss_cell[size].y = y;
        size++;
    }
    if(x != w-2 && maze[y * w + (x+2)] != -1){
        poss_cell[size].x = x+2;
        poss_cell[size].y = y;
        size++;
    }

    if(y != 1 && maze[(y-2) * w + x] != -1){
        poss_cell[size].x = x;
        poss_cell[size].y = y-2;
        size++;
    }
    if(y != h-2 && maze[(y+2) * w + x] != -1){
        poss_cell[size].x = x;
        poss_cell[size].y = y+2;
        size++;
    }

    if(size==0) {
        Cell cell = {-1,-1};
        return cell;
    }
    int r = rand()%size;
    return poss_cell[r];
}

void Rec_RandomDepthFirstSearch(int *maze, int w, int h, int x, int y) {
    maze[y * w + x] = -1; //marked as visited
    Cell cell;
    cell = getRandomNeighbours(maze, w, h, x, y);
    while (cell.x != -1){
        int x_wall = (x + cell.x)/2;
        int y_wall = (y + cell.y)/2;


        maze[y_wall * w + x_wall] = 0;
        Rec_RandomDepthFirstSearch(maze, w, h, cell.x, cell.y);
        cell = getRandomNeighbours(maze, w, h, x, y);
    }
}

void RandomDepthFirstSearch(int * maze, int w, int h){
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(x%2==1 && y%2==1){
                maze[y * w + x] = 0;
            } else {
                maze[y * w + x] = 1;
            }
        }
    }
    Rec_RandomDepthFirstSearch(maze, w, h, 1, 1);

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(maze[y * w + x] == -1){
                maze[y * w + x] = 0;
            }
        }
    }
}

void breakWalls(int * maze, int w, int h, int n){
    for(int i = 0; i < n; i++){
        int x = rand()%(w-2) + 1;
        int y = rand()%(h-2) + 1;
        maze[y * w + x] = 0;
    }
}

void printMaze(int * maze, int w, int h){
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            printf("%d",maze[y * w + x]);
        }
        printf("\n");
    }
}
