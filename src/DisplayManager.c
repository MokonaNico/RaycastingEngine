//
// Created by mine- on 28-08-21.
//

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayManager.h"
#include "Raycasting.h"

SDL_Window * window;
SDL_Renderer * renderer;

TTF_Font * fonts [MAX_FONT];
int fonts_size = 0;

// Raycast variable
uint32_t * pixels;

RenderObject tab [MAX_RENDER_OBJ];
int tab_size = 0;

/**
 * Create the window and the renderer. It also create the raycast.
 */
void createDisplay(char * title, int fullScreen){
    TTF_Init();

    // Init window and renderer
    int flags = 0;
    if (fullScreen) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags);
    renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    initRaycastTexture();
}

/**
 * Update the display, need to be call in the loop to draw thing on the screen.
 * It draw only what is in the table named tab.
 */
void updateDisplay(){
    SDL_RenderClear(renderer);

    // If the raycast render is enable, we update the texture.
    if(tab[0].isDisplayed){
        floor_ceiling_casting();
        wall_casting();
        SDL_UpdateTexture(tab[0].texture, NULL, pixels, WIDTH * sizeof(uint32_t));
    }

    // Going in reverse so element with the lowest index are rendered first
    for(int i = tab_size; i >= 0; i--){
        if(tab[i].isDisplayed){
            SDL_RenderCopy(renderer, tab[i].texture, NULL, tab[i].rect);
        }
    }

    SDL_RenderPresent(renderer);
}

/**
 * Free everything that as been created in this script
 */
void closeDisplay(){


    for(int i = 0; i < fonts_size; i++){
        TTF_CloseFont(fonts[i]);
    }
    TTF_Quit();


    free(pixels);
    printf("%d\n", tab_size);
    for(int i = 0; i < tab_size; i++){
        SDL_DestroyTexture(tab[i].texture);
        if(tab[i].rect != NULL) free(tab[i].rect);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * Add a render object to the tab of render object, increase the tab size
 * @param obj the render object to add
 */
void addRenderObject(RenderObject obj){
    tab[tab_size] = obj;
    tab_size++;
}

/**
 * Modify the information of a render object
 * @param index the index in the tab
 * @param x the x position of the texture
 * @param y the y position of the texture
 * @param w the width of the texture IF -1 then fullscreen
 * @param h the height of the texture
 * @param isDisplayed bool to say if it's going to be displayed or not
 */
void modifyRenderObject(int index, int x, int y, int w, int h, int isDisplayed){
    if(w == -1 || h == -1){
        SDL_GetRendererOutputSize(renderer, &w, &h);
    }
    if(tab[index].rect != NULL) free(tab[index].rect);
    tab[index].rect = malloc(sizeof(SDL_Rect));
    tab[index].rect->x = x;
    tab[index].rect->y = y;
    tab[index].rect->w = w;
    tab[index].rect->h = h;
    tab[index].isDisplayed = isDisplayed;
}

/**
 * Init the raycast texture with the pixel array
 */
void initRaycastTexture(){
    RenderObject raycastRender;
    raycastRender.surface = NULL;
    raycastRender.texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(window), SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    pixels = (uint32_t*) malloc(WIDTH * HEIGHT * sizeof(uint32_t));
    memset(pixels, 255, WIDTH * HEIGHT * sizeof(uint32_t));
    raycastRender.rect = NULL;
    raycastRender.isDisplayed = 0;
    addRenderObject(raycastRender);
}

/**
 * Set a pixel to a specific color for the raycast texture
 * @param x the x position
 * @param y the y position
 * @param color the color to apply
 */
void setPixel(int x, int y, ColorRGB color){
    pixels[y*WIDTH + x] = SDL_MapRGBA(SDL_AllocFormat(SDL_GetWindowPixelFormat(window)), color.r, color.g, color.b,0);
}

/**
 * Fill the raycast screen to black
 */
void clearRaycastScreen(){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            setPixel(x,y,BLACK);
        }
    }
}

/**
 * Create a render object from an image
 * @param file the file location of the image
 * @return the index number of the object
 */
int createRenderObjectFromImage(char * file){
    int index = tab_size;
    RenderObject renderObject;
    renderObject.surface = IMG_Load(file);
    renderObject.texture = SDL_CreateTextureFromSurface(renderer, renderObject.surface);
    renderObject.rect = NULL;
    renderObject.isDisplayed = 0;
    addRenderObject(renderObject);
    return index;
}

int createRenderObjectFromText(char * text, int font_index, ColorRGB color){
    SDL_Color sdlColor = {0,0,0};
    sdlColor.r = color.r; sdlColor.g = color.g; sdlColor.b = color.b; sdlColor.a = 255;
    int index = tab_size;
    RenderObject renderObject;
    printf("%d",fonts_size);
    renderObject.surface = TTF_RenderText_Solid(fonts[font_index], text, sdlColor);
    renderObject.texture = SDL_CreateTextureFromSurface(renderer, renderObject.surface);
    renderObject.rect = NULL;
    renderObject.isDisplayed = 0;
    addRenderObject(renderObject);
    return index;
}

/**
 * Get the screen resolution of the renderer
 * @param x a pointer to get the x size
 * @param y a pointer to get the y size
 */
void getScreenResolution(int * x, int * y){
    SDL_GetRendererOutputSize(renderer,x,y);
}

int loadFont(char * file, int size){
    fonts[fonts_size] = TTF_OpenFont(file, size);
    int index = fonts_size;
    fonts_size++;
    return index;
}