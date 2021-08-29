//
// Created by mine- on 28-08-21.
//
#include <SDL2/SDL.h>
#include <math.h>
#include "EventHandler.h"
#include "World.h"

SDL_Event event;
int quit = 0;

int up_pressed = 0;
int down_pressed = 0;
int left_pressed = 0;
int right_pressed = 0;

void keyDown(){
    switch( event.key.keysym.sym){
        case SDLK_ESCAPE:
            quit=1;
            break;
        case SDLK_UP:
            up_pressed = 1;
            break;
        case SDLK_DOWN:
            down_pressed = 1;
            break;
        case SDLK_LEFT:
            left_pressed = 1;
            break;
        case SDLK_RIGHT:
            right_pressed = 1;
            break;
    }
}

void keyUp(){
    switch( event.key.keysym.sym){
        case SDLK_UP:
            up_pressed = 0;
            break;
        case SDLK_DOWN:
            down_pressed = 0;
            break;
        case SDLK_LEFT:
            left_pressed = 0;
            break;
        case SDLK_RIGHT:
            right_pressed = 0;
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

