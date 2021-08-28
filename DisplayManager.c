//
// Created by mine- on 28-08-21.
//

#include <SDL2/SDL.h>
#include "DisplayManager.h"

int FULLSCREEN = 0;

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * texture;
uint32_t * pixels;

void createDisplay(){
    SDL_Init(SDL_INIT_VIDEO);
    int flags = 0;
    if(FULLSCREEN) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    window = SDL_CreateWindow("Raycasting3D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

    pixels = (uint32_t*) malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    memset(pixels, 255, WIDTH * HEIGHT * sizeof(uint32_t));
}

void updateDisplay(){
    SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void closeDisplay(){
    free(pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setPixel(int x, int y, ColorRGB color){
    pixels[y*WIDTH + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 0,color.b,color.g,color.r);
}

void setTitle(char * title){
    SDL_SetWindowTitle(window,title);
}