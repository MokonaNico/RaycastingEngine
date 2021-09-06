//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_DISPLAYMANAGER_H
#define RAYCASTINGENGINE_DISPLAYMANAGER_H

#include "Color.h"
#include <SDL2/SDL.h>

#define WIDTH 480 //640
#define HEIGHT 270 //480
#define MAX_RENDER_OBJ 32
#define MAX_FONT 32

typedef struct {
    SDL_Surface * surface;
    SDL_Texture * texture;
    SDL_Rect * rect;
    int isDisplayed;
} RenderObject;

void createDisplay(char * title, int fullScreen);
void updateDisplay();
void closeDisplay();
void setPixel(int x, int y, ColorRGB color);
void clearRaycastScreen();
void initRaycastTexture();
void modifyRenderObject(int index, int x, int y, int w, int h, int isDisplayed);
int createRenderObjectFromImage(char * file);
int createRenderObjectFromText(char * text, int font_index, ColorRGB color);
void getScreenResolution(int * x, int * y);
int loadFont(char * file, int size);

#endif //RAYCASTINGENGINE_DISPLAYMANAGER_H

