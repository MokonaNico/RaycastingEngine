//
// Created by mine- on 28-08-21.
//

#include "Color.h"
ColorRGB RED = {255,0,0};
ColorRGB GREEN = {255,0,0};
ColorRGB BLUE = {0,0,255};
ColorRGB WHITE = {255,255,255};
ColorRGB BLACK = {0,0,0};
ColorRGB YELLOW = {255,255,0};

ColorRGB divide(ColorRGB color){
    ColorRGB res = {color.r/2, color.g/2, color.b/2};
    return res;
}