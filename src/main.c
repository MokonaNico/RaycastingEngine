#include <SDL2/SDL.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "TextureManager.h"
#include "World.h"
#include "FontHandler.h"

int main(int argc, char* argv[]) {

    double time = 0;
    double oldTime = 0;

    createDisplay("Raycasting 3D", 1);
    modifyRenderObject(0,0,0,-1,-1,1);

    load_textures("res/images/stone.png");
    load_textures("res/images/stone2.png");
    load_textures("res/images/wood.png");


    load_world("res/maps/map0.map",20,20);
    startFont();

    while (!quit){
        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0;

        checkEvents();
        doMovements(frameTime);
        updateDisplay();
    }

    closeDisplay();
    closeFont();

    return 0;
}



/*
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Event event;
    SDL_Color white = {255, 255, 255};
    int continuer = 1;

    SDL_Window * window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,500, 500, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

    SDL_Surface *sfond = IMG_Load("res/images/blue.png");
    SDL_Texture *fond = SDL_CreateTextureFromSurface(renderer, sfond);

    TTF_Font *font = TTF_OpenFont("res/font/ARCADECLASSIC.TTF", 200);

    SDL_Surface *stext = TTF_RenderText_Solid(font, "Hello world !", white);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, stext);
    SDL_Rect trect;
    trect.x = 0;
    trect.y = 0;
    trect.w = 400;
    trect.h = 100;


    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }



        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fond, NULL, NULL);
        SDL_RenderCopy(renderer, text, NULL, &trect);
        SDL_RenderPresent(renderer);
    }


    SDL_FreeSurface(stext);
    SDL_DestroyTexture(text);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
 */