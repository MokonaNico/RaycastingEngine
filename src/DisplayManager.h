//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_DISPLAYMANAGER_H
#define RAYCASTINGENGINE_DISPLAYMANAGER_H

#include "Color.h"

#define WIDTH 480 //640
#define HEIGHT 270 //480
#define FULLSCREEN 1

void createDisplay();
void updateDisplay();
void closeDisplay();
void setPixel(int x, int y, ColorRGB color);
void clearScreen();


#endif //RAYCASTINGENGINE_DISPLAYMANAGER_H

