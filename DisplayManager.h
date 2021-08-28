//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_DISPLAYMANAGER_H
#define RAYCASTINGENGINE_DISPLAYMANAGER_H

#include "Color.h"

#define WIDTH 480
#define HEIGHT 270

void createDisplay();
void updateDisplay();
void closeDisplay();
void setPixel(int x, int y, ColorRGB color);
void setTitle(char title[]);

#endif //RAYCASTINGENGINE_DISPLAYMANAGER_H

