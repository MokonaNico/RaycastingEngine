//
// Created by mine- on 28-08-21.
//

#include <math.h>
#include "Raycasting.h"
#include "DisplayManager.h"
#include "World.h"
#include "TextureManager.h"

int ceilingTexture = -1;
int floorTexture = -1;

double ZBuffer[WIDTH];

int spriteOrder[MAX_SPRITE];
double spriteDistance[MAX_SPRITE];


void setTextures(int floor, int ceiling){
    ceilingTexture = ceiling;
    floorTexture = floor;
}

void floorCeilingCasting(){
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
            color = getPixel(floorTexture, tx, ty);
            setPixel(x,y,color);

            //ceiling
            color = getPixel(ceilingTexture, tx, ty);
            setPixel(x, HEIGHT-y-1, color);
        }
    }
}

void wallCasting(){
    for(int x = 0; x < WIDTH; x++){
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = dir.x + plane.x * cameraX;
        double rayDirY = dir.y + plane.y * cameraX;

        int mapX = (int) pos.x;
        int mapY = (int) pos.y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1.0f / rayDirX);
        double deltaDistY = fabs(1.0f / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

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
            if (getWorldCase(mapX, mapY) > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - pos.x + (1.0 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - pos.y + (1.0 - stepY) / 2) / rayDirY;

        int lineHeight = (int) ((HEIGHT / perpWallDist));

        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

        int texNum = getWorldCase(mapX, mapY) - 1;

        double wallX;
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
            int texY = (int)texPos & (TEX_SIZE - 1);
            texPos += step;
            ColorRGB color = getPixel(texNum, texX, texY);
            if(side == 1) color = divide(color);
            setPixel(x,y,color);
        }
        ZBuffer[x] = perpWallDist;
    }
}

void sortSprite(int* order, const double* dist){
    int swap = 0;
    do{
        swap = 0;
        for(int i = 1; i < sprite_length;i++){
            if(dist[order[i-1]] < dist[order[i]]){
                int a = order[i];
                order[i] = order[i-1];
                order[i-1] = a;
                swap = 1;
            }
        }
    } while (swap);
}

void spriteCasting(){
    for(int i = 0; i < sprite_length; i++){
        spriteOrder[i] = i;
        spriteDistance[i] = dist(pos, sprites[i].pos);
    }

    sortSprite(spriteOrder, spriteDistance);

    for(int i = 0; i < sprite_length; i++){
        Vector sprite;
        sprite.x = sprites[spriteOrder[i]].pos.x - pos.x;
        sprite.y = sprites[spriteOrder[i]].pos.y - pos.y;

        double invDet = 1.0 / (plane.x * dir.y - dir.x * plane.y);
        Vector transform;
        transform.x = invDet * (dir.y * sprite.x - dir.x * sprite.y);
        transform.y = invDet * (-plane.y * sprite.x + plane.x * sprite.y);

        int spriteScreenX = (int) ((WIDTH/2.0) * (1 + transform.x / transform.y));

        int spriteHeight = abs((int) (HEIGHT / (transform.y)));
        int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + HEIGHT / 2;
        if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

        int spriteWidth = abs( (int) (HEIGHT / (transform.y)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

        for(int stripe = drawStartX; stripe < drawEndX; stripe++) {
            int texX = (int) (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_SIZE / spriteWidth) / 256;
            if(transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < ZBuffer[stripe]){
                for(int y = drawStartY; y < drawEndY; y++) {
                    int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128;
                    int texY = ((d * TEX_SIZE) / spriteHeight) / 256;

                    ColorRGB color = getPixel(sprites[spriteOrder[i]].texture, texX, texY);
                    if(!(color.r == 0 && color.g == 0 && color.b == 0)){
                        setPixel(stripe, y, color);
                    }
                }
            }
        }
    }
}