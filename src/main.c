#include <SDL2/SDL.h>
#include <stdio.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "Raycasting.h"
#include "TextureManager.h"

int main(int argc, char* argv[]) {

    double time = 0;
    double oldTime = 0;

    createDisplay();
    load_textures();

    while (!quit){

        clearScreen();

        floor_ceiling_casting();
        wall_casting();

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
