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

int state = 0;

double time = 0;
double oldTime = 0;

int maze_w = 0;
int maze_h = 0;
int * maze;

void generateMaze(int w, int h){
    maze_w = w;
    maze_h = h;
    if(maze != NULL) free(maze);
    maze = malloc(sizeof(int) * maze_w * maze_h);
    RandomDepthFirstSearch(maze, maze_w, maze_h);
    setWorld(maze, maze_w, maze_h);

    printMaze(maze, w, h);
    setPlayer(1.5,1.5,0,1);
    modifySprite(0,maze_w-2+0.5,maze_h-2+0.5);
}

void menu(){
    int x,y;
    getScreenResolution(&x,&y);
    modifyRenderObject(1,x/2 - 250,y/8,500,200,1);
    modifyRenderObject(2,x/2 - 100,y/8 + 300,200,100,1);
    modifyRenderObject(3,x/2 - 100,y/8 + 400,275,100,1);
    modifyRenderObject(4,x/2 - 100,y/8 + 500,200,100,1);
    if(one_pressed || two_pressed || three_pressed){
        if(one_pressed) generateMaze(21,21);
        if(two_pressed) generateMaze(51,51);
        if(three_pressed) generateMaze(101,101);

        modifyRenderObject(1,x/2 - 250,y/8,500,200,0);
        modifyRenderObject(2,x/2 - 100,y/8 + 300,200,100,0);
        modifyRenderObject(3,x/2 - 100,y/8 + 400,275,100,0);
        modifyRenderObject(4,x/2 - 100,y/8 + 500,200,100,0);
        state = 1;
    }
}

void game(){
    modifyRenderObject(0,0,0,-1,-1,1);

    oldTime = time;
    time = SDL_GetTicks();
    double frameTime = (time - oldTime) / 1000.0;
    if(pos.x >= maze_w-2 && pos.x <= maze_w-1 && pos.y >= maze_h-2 && pos.x <= maze_h-1){
        modifyRenderObject(0,0,0,-1,-1,0);
        state = 2;
    }

    doMovements(frameTime);
}

void win(){
    int x,y;
    getScreenResolution(&x,&y);
    modifyRenderObject(5,x/2 - 250,250,500,150,1);
    modifyRenderObject(6,x/2 - 500,500,1000,150,1);
    if(enter_pressed){
        modifyRenderObject(5,0,0,500,500,0);
        modifyRenderObject(6,0,500,500,500,0);
        state = 0;
    }
}


int main(int argc, char* argv[]) {

    createDisplay("Maze Game", 1);

    loadTextures("res/images/stone.png");
    loadTextures("res/images/stone2.png");
    loadTextures("res/images/wood.png");
    loadTextures("res/images/trophy.png");
    loadFont("res/font/ARCADECLASSIC.TTF",22);

    createRenderObjectFromText("MAZE    GAME",0, WHITE);
    createRenderObjectFromText("1 EASY",0, WHITE);
    createRenderObjectFromText("2 NORMAL",0, WHITE);
    createRenderObjectFromText("3 HARD",0, WHITE);

    createRenderObjectFromText("YOU    WIN    !!!",0,WHITE);
    createRenderObjectFromText("PRESS    ENTER    TO    RETURN    TO    MENU",0,WHITE);

    setTextures(1,2);

    addSprite(0,0,3);

    while (!quit){
        checkEvents();

        if(state == 0){
            menu();
        } else if (state == 1){
            game();
        } else if (state == 2){
            win();
        }

        updateDisplay();
    }

    closeDisplay();
    closeWorld();
    return 0;
}
