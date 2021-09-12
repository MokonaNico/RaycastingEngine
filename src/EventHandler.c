//
// Created by mine- on 28-08-21.
//
#include <SDL2/SDL.h>
#include "EventHandler.h"

#define up_button SDLK_z
#define down_button SDLK_s
#define left_button SDLK_q
#define right_button SDLK_d
#define strafe_left_button SDLK_a
#define strafe_right_button SDLK_e




SDL_Event event;
int quit = 0;

int up_pressed = 0;
int down_pressed = 0;
int left_pressed = 0;
int right_pressed = 0;
int strafe_left_pressed = 0;
int strafe_right_pressed = 0;

int one_pressed = 0;
int two_pressed = 0;
int three_pressed = 0;

int enter_pressed = 0;

void keyDown(){
    switch( event.key.keysym.sym){
        case SDLK_ESCAPE:
            quit=1;
            break;
        case up_button:
            up_pressed = 1;
            break;
        case down_button:
            down_pressed = 1;
            break;
        case left_button:
            left_pressed = 1;
            break;
        case right_button:
            right_pressed = 1;
            break;
        case strafe_left_button:
            strafe_left_pressed = 1;
            break;
        case strafe_right_button:
            strafe_right_pressed = 1;
            break;
        case SDLK_1:
            one_pressed = 1;
            break;
        case SDLK_2:
            two_pressed = 1;
            break;
        case SDLK_3:
            three_pressed = 1;
            break;
        case SDLK_RETURN:
            enter_pressed = 1;
            break;
    }
}

void keyUp(){
    switch( event.key.keysym.sym){
        case up_button:
            up_pressed = 0;
            break;
        case down_button:
            down_pressed = 0;
            break;
        case left_button:
            left_pressed = 0;
            break;
        case right_button:
            right_pressed = 0;
            break;
        case strafe_left_button:
            strafe_left_pressed = 0;
            break;
        case strafe_right_button:
            strafe_right_pressed = 0;
            break;
        case SDLK_1:
            one_pressed = 0;
            break;
        case SDLK_2:
            two_pressed = 0;
            break;
        case SDLK_3:
            three_pressed = 0;
            break;
        case SDLK_RETURN:
            enter_pressed = 0;
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

