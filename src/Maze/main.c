//
// Created by mine- on 09-09-21.
//

#include <SDL2/SDL.h>
#include "../DisplayManager.h"
#include "../EventHandler.h"
#include "../TextureManager.h"
#include "../World.h"
#include "../Raycasting.h"
#include "MazeGenerator.h"

int main(int argc, char* argv[]) {
    double time = 0;
    double oldTime = 0;

    createDisplay("Maze Game", 1);
    modifyRenderObject(0,0,0,-1,-1,1);
    loadTextures("res/images/stone.png");
    loadTextures("res/images/stone2.png");
    loadTextures("res/images/wood.png");
    loadTextures("res/images/barrel.png");
    loadTextures("res/images/lamp.png");

    setTextures(1,2);
    setPlayer(1.5,1.5,0,1);

    int maze_w = 51;
    int maze_h = 51;
    int * maze;
    maze = malloc(sizeof(int) * maze_w * maze_h);
    RandomDepthFirstSearch(maze, maze_w, maze_h);

    setWorld(maze, maze_w, maze_h);

    while (!quit){
        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;

        checkEvents();
        doMovements(frameTime);
        updateDisplay();
    }

    closeDisplay();
    closeWorld();
    return 0;
}
