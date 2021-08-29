//
// Created by mine- on 29-08-21.
//

#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Surface * textures[5];

void load_textures(){

    textures[0] = IMG_Load("res/images/stone.png");
    if(!textures[0]) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    textures[1] = IMG_Load("res/images/stone2.png");
    if(!textures[1]) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    textures[2] = IMG_Load("res/images/wood.png");
    if(!textures[2]) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    textures[3] = IMG_Load("res/images/blue.png");
    if(!textures[3]) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    textures[4] = IMG_Load("res/images/flag.png");
    if(!textures[4]) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
}

ColorRGB get_pixel(int texture_number, int x, int y){
    SDL_Surface * surface = textures[texture_number];
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 1;
    Uint8 r,g,b;
    SDL_GetRGB(*p,textures[texture_number]->format,&r,&g,&b);
    ColorRGB color = {r,g,b};
    return color;
}
