#include"libs/UI.h"
#include"libs/Systems.h"

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

    loadTextures(renderer);

    int pInput = 0;
    int gameState = ACTIVE;
    SDL_Event event;

    // TODO: When setting the stage set the current world size as well
    while (gameState){
        SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
        SDL_RenderClear(renderer);
        handleInput(&event, &gameState, &pInput);
        if (gameState == ACTIVE){
            handlePlayerMovement(&pInput);
            UpdateWorld();
            RenderWorld(renderer);
        } else {
            UpdateUI(&gameState);
            RenderUI(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(atlas);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
