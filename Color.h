//
// Created by mine- on 28-08-21.
//

#ifndef RAYCASTINGENGINE_COLOR_H
#define RAYCASTINGENGINE_COLOR_H

typedef struct {
    int r;
    int g;
    int b;
} ColorRGB;

ColorRGB RED;
ColorRGB GREEN;
ColorRGB BLUE;
ColorRGB WHITE;
ColorRGB BLACK;
ColorRGB YELLOW;

ColorRGB divide(ColorRGB color);

#endif //RAYCASTINGENGINE_COLOR_H
