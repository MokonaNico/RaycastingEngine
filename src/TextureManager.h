//
// Created by mine- on 29-08-21.
//

#ifndef RAYCASTINGENGINE_TEXTUREMANAGER_H
#define RAYCASTINGENGINE_TEXTUREMANAGER_H

#include "Color.h"

#define TEX_SIZE 64

void load_textures();
ColorRGB get_pixel(int texture_number, int x, int y);

#endif //RAYCASTINGENGINE_TEXTUREMANAGER_H
