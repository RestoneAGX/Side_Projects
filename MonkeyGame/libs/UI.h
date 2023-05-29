#include<SDL2/SDL.h>
#include "player.h"

#define MENU_SIZE 4
#define button_pressed(rec, mx, my)( !(rec.x < mx || rec.x + rec.w > mx || rec.y < my || rec.y + rec.h > my))


typedef struct UI_Element{
    char id;
    SDL_Rect* src;
    SDL_FRect pos;
}UI_Element;

UI_Element UI[2][4] = { // NOTE: Maybe reuse the normal screen and swap the Text Texture to "Game Over" Instead of "Paused"
    {}, // NORMAL / Pause Menu
    {
        // TODO: Place Text here with "GameOver written"
        // TODO: Place Restart button
        // TODO: Place Quit Button
    }, // GAME_OVER Screen
};

int menuState = 0;

SDL_Texture *atlas;

void MenuFunc(char id, int* gameState){
    if (!id){
        *gameState = QUIT; 
        return;
    }
    current_world_size = 2;
    world[1] = presets[id-1];
    // TODO: set the reset point para la position
    world[plr].pos.x = 100;
    world[plr].pos.y = 560;
}

void UpdateUI(int* gameState){
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    for ( int i = 0; i < 4; i++ ){
        if ( button_pressed(UI[menuState][i].pos, x, y) )
            MenuFunc(UI[menuState][i].id, gameState);
    }
}

inline void RenderUI(SDL_Renderer* renderer){
    for (int i = 0; i < MENU_SIZE; i++)
        SDL_RenderCopyF(renderer, atlas, UI[menuState][i].src, &UI[menuState][i].pos);
}

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
