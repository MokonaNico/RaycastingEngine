//
// Created by mine- on 05-09-21.
//

#include <SDL2/SDL_ttf.h>
#include "FontHandler.h"

TTF_Font *font = NULL;

void startFont(){
    TTF_Init();
    font = TTF_OpenFont("res/font/ARCADECLASSIC.TTF", 22);
}

void closeFont(){
    TTF_CloseFont(font);
    TTF_Quit();
}

