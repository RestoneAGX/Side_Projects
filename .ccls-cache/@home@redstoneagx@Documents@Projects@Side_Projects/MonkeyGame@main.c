#include<stdio.h>
#include<SDL2/SDL.h>
#include"libs/player.h"

#define WIN_HEIGHT 680
#define WIN_WIDTH 1048

int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_EVERYTHING))
        return printf("Init Error: %s\n", SDL_GetError());
    SDL_Window* window = SDL_CreateWindow("Monkey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    if (!window){
        SDL_Quit();
        return printf("Error Creating Window: %s\n", SDL_GetError());
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        SDL_DestroyWindow(window);
        SDL_Quit();
        return printf("Error Creating Renderer: %s\n", SDL_GetError());
    }

    loadTextures();

    int pInput[] = {0,0};
    int gameActive = 1;
    SDL_Event event;

    while (gameActive){
        handleInput(&gameActive, &event, pInput);
        renderWorld(renderer);
    }

    SDL_DestroyTexture(atlas);
    return 0;
}
