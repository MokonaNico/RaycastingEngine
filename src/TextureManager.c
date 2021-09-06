//
// Created by mine- on 29-08-21.
//

#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Surface * textures[MAX_TEXTURE];
int texture_size = 0;

int load_textures(char * file){
    textures[texture_size] = IMG_Load(file);
    if(!textures[texture_size]) {
        printf("IMG_Load: %s\n", IMG_GetError());
    }
    texture_size++;
    return texture_size-1;
}

ColorRGB get_pixel(int texture_number, int x, int y){
    SDL_Surface * surface = textures[texture_number];
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * 1;
    Uint8 r,g,b;
    SDL_GetRGB(*p,textures[texture_number]->format,&r,&g,&b);
    ColorRGB color = {r,g,b};
    return color;
}
