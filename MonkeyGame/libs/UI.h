#include<SDL2/SDL.h>
#include<player.h>

#define button_pressed(rec, mx, my)( !(rec.x < mx || rec.x + rec.w > mx || rec.y < my || rec.y + rec.h > my))

typedef struct UI_Element{
    char id;
    SDL_Rect* src;
    SDL_FRect pos;
}UI_Element;

UI_Element UI[4] = {};

void MenuFunc(char id, int* gameState){
    if (!id){
        *gameState = QUIT; 
        return;
    }
    current_world_size = 2;
    world[1] = presets[id];
    // TODO: set the reset point para la position
    world[plr].pos.x = 0;
    world[plr].pos.y = 0;
}

void UpdateUI(int* gameState){
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    for ( int i = 0; i < 4; i++ ){
        if ( button_pressed(UI[i].pos, x, y) )
            MenuFunc(UI[i].id, gameState);
    }
}

inline void RenderUI(SDL_Renderer* renderer){
    for (int i = 0; i < 4; i++)
        SDL_RenderCopyF(renderer, atlas, UI[i].src, &UI[i].pos)
}