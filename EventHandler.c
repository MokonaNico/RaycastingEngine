//
// Created by mine- on 28-08-21.
//
#include <SDL2/SDL.h>
#include "EventHandler.h"

SDL_Event event;
int quit = 0;

int is_up_pressed = 0;
int is_down_pressed = 0;
int is_left_pressed = 0;
int is_right_pressed = 0;

void keyDown(){
    switch( event.key.keysym.sym){
        case SDLK_ESCAPE:
            quit=1;
            break;
        case SDLK_UP:
            is_up_pressed = 1;
            break;
        case SDLK_DOWN:
            is_down_pressed = 1;
            break;
        case SDLK_LEFT:
            is_left_pressed = 1;
            break;
        case SDLK_RIGHT:
            is_right_pressed = 1;
            break;
    }
}

void keyUp(){
    switch( event.key.keysym.sym){
        case SDLK_UP:
            is_up_pressed = 0;
            break;
        case SDLK_DOWN:
            is_down_pressed = 0;
            break;
        case SDLK_LEFT:
            is_left_pressed = 0;
            break;
        case SDLK_RIGHT:
            is_right_pressed = 0;
            break;
    }
}


void checkEvents(){
    if ( SDL_PollEvent( &event ) ) {
        switch (event.type) {
            case SDL_QUIT:
                quit=1;
                break;
            case SDL_KEYDOWN:
                keyDown();
                break;
            case SDL_KEYUP:
                keyUp();
                break;
        }
    }
}

