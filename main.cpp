#include <cstdio>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <ctime>

#define WIDTH 200
#define HEIGHT 200


int main(int argc, char* argv[])
{
    bool quit = false;

    SDL_Event event;

    //uint32_t pixels[WIDTH*HEIGHT];
    uint32_t * pixels = (uint32_t*) malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    memset(pixels, 255, WIDTH * HEIGHT * sizeof(uint32_t));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Test pixel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

    SDL_Texture * texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

    srand(time(NULL));

    while (!quit){
        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(uint32_t));

        if ( SDL_PollEvent( &event ) ) {
            switch (event.type) {
                case SDL_QUIT:
                    quit=true;
                    break;
            }
        }

        for(int x=0; x < WIDTH; x++){
            for(int y=0; y < HEIGHT; y++){
                int r = rand()%255;
                int g = rand()%255;
                int b = rand()%255;
                int a = rand()%255;
                pixels[y*WIDTH + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), r,g,b,a);
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(pixels);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
