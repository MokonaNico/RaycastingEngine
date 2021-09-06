//
// Created by mine- on 28-08-21.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "DisplayManager.h"

SDL_Window * window;
SDL_Renderer * renderer;

// Raycast variable
SDL_Texture * raycastTexture;
uint32_t * pixels;

// Menu variable
SDL_Surface * menuBackgroundSurface;
SDL_Texture * menuBackground;
SDL_Rect menuBackgroundRect = {0,0,WIDTH,HEIGHT};

void createDisplay(){
    // Init window and renderer
    int flags = 0;
    if(FULLSCREEN) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    window = SDL_CreateWindow("Raycasting3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WIDTH, HEIGHT, flags);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

    // Init raycasting
    raycastTexture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    pixels = (uint32_t*) malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    memset(pixels, 255, WIDTH * HEIGHT * sizeof(uint32_t));

    // Init main menu
    menuBackgroundSurface = IMG_Load("res/images/menu.png");
    menuBackground = SDL_CreateTextureFromSurface(renderer,menuBackgroundSurface);
}

void updateDisplay(int state){
    SDL_RenderClear(renderer);

    if(state == 0){
        // RAYCAST
        SDL_UpdateTexture(raycastTexture, NULL, pixels, WIDTH * sizeof(uint32_t));
        SDL_RenderCopy(renderer, raycastTexture, NULL, NULL);
    } else if (state == 1){
        SDL_GetRendererOutputSize(renderer, &menuBackgroundRect.w, &menuBackgroundRect.h);
        // MAIN MENU
        SDL_RenderCopy(renderer, menuBackground, NULL, &menuBackgroundRect);
    }

    SDL_RenderPresent(renderer);
}

void closeDisplay(){
    free(pixels);
    SDL_DestroyTexture(raycastTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setPixel(int x, int y, ColorRGB color){
    pixels[y*WIDTH + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_GetWindowPixelFormat(window)), color.r, color.g, color.b,0);
}

void clearScreen(){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            setPixel(x,y,RED);
        }
    }
}