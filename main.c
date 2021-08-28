#include <SDL2/SDL.h>
#include <stdio.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "Raycasting.h"

int main(int argc, char* argv[]) {

    double lastFPSUpdateFrame = 0;
    double time = 0;
    double oldTime = 0;

    createDisplay();

    while (!quit){

        clearScreen();
        compute_raycast();

        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;
        if(time > lastFPSUpdateFrame + 500){
            char * title = (char*)malloc(60 * sizeof(char));
            sprintf(title, "%f", 1.0 / frameTime);
            setTitle(title);
            lastFPSUpdateFrame = time;
        }

        checkEvents();
        doMovements(frameTime);
        updateDisplay();
    }
    closeDisplay();
    return 0;
}
