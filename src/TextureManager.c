//
// Created by mine- on 29-08-21.
//

#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define nbr_texture 5

char arr[nbr_texture][128] = {
        "res/images/stone.png",
        "res/images/stone2.png",
        "res/images/wood.png",
        "res/images/blue.png",
        "res/images/flag.png"
};

SDL_Surface * textures[nbr_texture];

void load_textures(){
    for(int i = 0; i < nbr_texture; i++){
        textures[i] = IMG_Load(arr[i]);
        if(!textures[i]) {
            printf("IMG_Load: %s\n", IMG_GetError());
        }
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
