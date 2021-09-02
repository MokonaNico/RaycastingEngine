#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "Raycasting.h"
#include "TextureManager.h"
#include "World.h"

int main(int argc, char* argv[]) {
    int state = 1;

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
        if(state == 0){

        } else {
            doMovements(frameTime);
            clearScreen();
            floor_ceiling_casting();
            wall_casting();
        }
        updateDisplay();
    }
    closeDisplay();
    return 0;
}
