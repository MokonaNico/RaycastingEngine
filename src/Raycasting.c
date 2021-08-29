//
// Created by mine- on 28-08-21.
//

#include <math.h>
#include "Raycasting.h"
#include "DisplayManager.h"
#include "World.h"
#include "TextureManager.h"

#define ceiling_texture 0
#define floor_texture 1

void floor_ceiling_casting(){
    for(int y = 0; y < HEIGHT; y++)
    {
        double rayDirX0 = dir.x - plane.x;
        double rayDirY0 = dir.y - plane.y;
        double rayDirX1 = dir.x + plane.x;
        double rayDirY1 = dir.y + plane.y;

        int p = y - HEIGHT / 2;
        double posZ = 0.5 * HEIGHT;

        double rowDistance = posZ / (double) p;

        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;
        double floorX = pos.x + rowDistance * rayDirX0;
        double floorY = pos.y + rowDistance * rayDirY0;

        for(int x = 0; x < WIDTH; ++x)
        {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            int tx = (int)(TEX_SIZE * (floorX - cellX)) & (TEX_SIZE - 1);
            int ty = (int)(TEX_SIZE * (floorY - cellY)) & (TEX_SIZE - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            ColorRGB color;

            // floor
            color = get_pixel(floor_texture, tx, ty);
            setPixel(x,y,color);

            //ceiling
            color = get_pixel(ceiling_texture, tx, ty);
            setPixel(x, HEIGHT-y-1, color);
        }
    }
}

void wall_casting(){
    for(int x = 0; x < WIDTH; x++){
        double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        double rayDirX = dir.x + plane.x * cameraX;
        double rayDirY = dir.y + plane.y * cameraX;

        //which box of the map we're in
        int mapX = (int) pos.x;
        int mapY = (int) pos.y;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1.0f / rayDirX);
        double deltaDistY = fabs(1.0f / rayDirY);
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
        }

        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (get_world_case(mapX,mapY) > 0) hit = 1;
        }

        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - pos.x + (1.0 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - pos.y + (1.0 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int) ((HEIGHT / perpWallDist));

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

        int texNum = get_world_case(mapX,mapY) - 1;

        double wallX; //where exactly the wall was hit
        if (side == 0) wallX = pos.y + perpWallDist * rayDirY;
        else           wallX = pos.x + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        int texX = (int) (wallX * (double) TEX_SIZE);
        if(side == 0 && rayDirX > 0) texX = TEX_SIZE - texX - 1;
        if(side == 1 && rayDirY < 0) texX = TEX_SIZE - texX - 1;

        double step = 1.0 * TEX_SIZE / lineHeight;
        double texPos = (drawStart - HEIGHT / 2.0 + lineHeight / 2.0) * step;
        for(int y = drawStart; y<drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (TEX_SIZE - 1);
            texPos += step;

            ColorRGB color = get_pixel(texNum, texX, texY);
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(side == 1) color = divide(color);
            setPixel(x,y,color);
        }
    }
}