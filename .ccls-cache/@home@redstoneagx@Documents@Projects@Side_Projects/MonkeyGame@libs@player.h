#include<SDL2/SDL.h>

#define WORLD_SIZE 50

typedef struct entity{
    unsigned char components[4]; // id: 0, hp: 1, rest are cooldown
    SDL_Rect* src;
    SDL_FRect pos;
} entity;

entity world[WORLD_SIZE]; // player: 0, boss: 1, rest is projectiles
int currentWorldSize = 1;

SDL_Texture* atlas; // TODO: add the background as the last element of the atlas 

void handleInput(int *gameActive, SDL_Event *event, int* input){
    while(SDL_PollEvent(event)){
        switch(event->type) {
            case SDL_QUIT: *gameActive = 0; 
            break;

            case SDL_KEYDOWN:
                switch(event->key.keysym.scancode){
                    case SDL_SCANCODE_A: input[0] = -1;
                        break;
                    case SDL_SCANCODE_D: input[0] = 1;
                        break;
                    case SDL_SCANCODE_S: input[1] = -1;
                        break;
                    case SDL_SCANCODE_W: input[1] = 1;
                        break;
                    default: break;
                }
            break;

            case SDL_KEYUP:
                switch(event->key.keysym.scancode){
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_D: input[0] = 0;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_W: input[1] = 0;
                        break;
                    default: break;
                }
            break;

            default: break;
        }
    }
}

void loadTextures(){
    SDL_Surface *img = SDL_LoadBMP("textures.bmp");
    SDL_Surface *opedImg = SDL_ConvertSurface(img, img->format, 0);
    atlas = SDL_CreateTextureFromSurface(renderer, opedImg);
    SDL_FreeSurface(img);
    SDL_FreeSurface(img);
}

void renderWorld(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    SDL_RenderClear(renderer);

    // Rendering the world
    for (int i = 0; i < WORLD_SIZE; i++)
        SDL_RenderCopyF(renderer, atlas, world[i].src, &world[i].pos); 

    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
}
