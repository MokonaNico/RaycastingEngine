#include <SDL2/SDL.h>
#include <stdio.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "TextureManager.h"
#include "World.h"
#include "Raycasting.h"

int main(int argc, char* argv[]) {
    double time = 0;
    double oldTime = 0;

    createDisplay("Raycasting 3D", 1);
    loadFont("res/font/ARCADECLASSIC.TTF",22);

    int texti = createRenderObjectFromText("Bonjour !", 0, WHITE);
    int imgi = createRenderObjectFromImage("res/images/blue.png");

    modifyRenderObject(0,200,200,600,600,1);
    modifyRenderObject(texti,10,0,200,100,1);
    modifyRenderObject(imgi,0,0,200,100,1);

    loadTextures("res/images/stone.png");
    loadTextures("res/images/stone2.png");
    loadTextures("res/images/wood.png");
    setTextures(1,2);
    setPlayer(1.5,1.5,0.5,0.5);
    loadWorld("res/maps/map0.map", 20, 20);

    while (!quit){
        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;

        checkEvents();
        doMovements(frameTime);
        updateDisplay();
    }

    closeDisplay();

    return 0;
}
