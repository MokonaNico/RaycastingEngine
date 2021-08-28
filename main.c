#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include "DisplayManager.h"
#include "EventHandler.h"
#include "World.h"

int main(int argc, char* argv[]) {

    double lastFPSUpdateFrame = 0;

    double posX = 22, posY = 12;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame

    createDisplay();

    while (!quit){

        for(int x = 0; x < WIDTH; x++){
            for(int y = 0; y < HEIGHT; y++){
                setPixel(x,y,BLACK);
            }
        }

        for(int x = 0; x < WIDTH; x++){
            double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            //which box of the map we're in
            int mapX = (int) posX;
            int mapY = (int) posY;

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
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }

            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (side == 0) perpWallDist = (mapX - posX + (1.0 - stepX) / 2) / rayDirX;
            else           perpWallDist = (mapY - posY + (1.0 - stepY) / 2) / rayDirY;

            //Calculate height of line to draw on screen
            int lineHeight = (int)(HEIGHT / perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + HEIGHT / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + HEIGHT / 2;
            if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

            ColorRGB color;
            switch(worldMap[mapX][mapY])
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

        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds

        // Allocates storage
        if(time > lastFPSUpdateFrame + 500){
            char * title = (char*)malloc(60 * sizeof(char));
            sprintf(title, "%f", 1.0 / frameTime);
            setTitle(title);
            lastFPSUpdateFrame = time;
        }

        //speed modifiers
        double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
        double rotSpeed = frameTime * 1.0; //the constant value is in radians/second

        if(is_right_pressed){
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }


        checkEvents();
        updateDisplay();
    }
    closeDisplay();
    return 0;
}
