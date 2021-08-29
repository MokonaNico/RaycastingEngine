//
// Created by mine- on 28-08-21.
//

#include <math.h>
#include "Raycasting.h"
#include "DisplayManager.h"
#include "World.h"

void compute_raycast(){
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

        ColorRGB color;
        switch(get_world_case(mapX,mapY))
        {
            case 1:  color = RED;  break; //red
            case 2:  color = GREEN;  break; //green
            case 3:  color = BLUE;   break; //blue
            case 4:  color = WHITE;  break; //white
            default: color = YELLOW; break; //yellow
        }

        if (side == 1) {
            color = divide(color);
        }

        for(int y = drawStart; y < drawEnd; y++){
            setPixel(x,y,color);
        }
    }
}