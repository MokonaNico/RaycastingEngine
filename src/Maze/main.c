//
// Created by mine- on 09-09-21.
//

#include "main.h"
#include <SDL2/SDL.h>
#include <stdio.h>
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
    loadWorld("res/maps/map0.map",20,20);

    addSprite(16.5,1.5, 3);
    addSprite(16.5,2.5, 3);
    addSprite(16.5,4.5, 3);
    addSprite(16.5,5.5, 3);
    addSprite(16.5,6.5, 3);

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
