#include <SDL2/SDL.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "Raycasting.h"
#include "TextureManager.h"
#include "World.h"

int main(int argc, char* argv[]) {
    double time = 0;
    double oldTime = 0;

    createDisplay();
    load_textures();
    load_world("res/maps/map0.map",20,20);

    while (!quit){
        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;

        checkEvents();
        doMovements(frameTime);

        clearScreen();
        floor_ceiling_casting();
        wall_casting();
        updateDisplay();
    }
    closeDisplay();
    return 0;
}
