#include<SDL2/SDL.h>

typedef struct UI_Element{
    (void*)()callback
    unsigned char data;
    SDL_Rect* src;
    SDL_FRect pos;
}UI_Element;