#include<SDL2/SDL.h>
#include "player.h"

SDL_Texture *atlas;

void loadTextures(SDL_Renderer* renderer){
    SDL_Surface* preop = SDL_LoadBMP("./resources/atlas.bmp");
    SDL_Surface* oped = SDL_ConvertSurface(preop, preop->format, 0);
    atlas = SDL_CreateTextureFromSurface(renderer, oped);
    SDL_FreeSurface(preop);
    SDL_FreeSurface(oped); 
}

inline void RenderWorld(SDL_Renderer* renderer){
    // TODO: Render background
    for (int i = 0; i < current_world_size; i++)
        SDL_RenderCopyF(renderer, atlas, world[i].src, &world[i].pos);
}
