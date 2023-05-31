#pragma once
#include<SDL2/SDL.h>

enum GameStates{
    QUIT,
    ACTIVE,
    PAUSED,
};

enum MenuStates{
    NORMAL,
    GAME_OVER,
};

enum Components{
    HP,
    ANIMATION,
    FLIPPED,
    DAMAGE,
    GRAVITY,
};

enum AnimationTypes{
    IDLE,
    SHOOT,
    ATK,
    SPECIAL,
};

enum Entities{
    plr,
    DK,
    Kranky,
    Leo,
    Drake,
    Kɔbe,
    Kane,
    Lightning,
    Bottle,
};

// Constants
#define COMPONENT_MAX 6
#define TIMER_MAX 3
#define Gravity 0.05

// Tools
#define bounds_check(pos1,pos2)( !(pos1.x < pos2.x || pos1.x + pos1.w > pos2.x + pos2.w || pos1.y < pos2.y ||  pos1.y + pos1.h > pos2.y + pos2.h) )

#define entity(i, state, hp, flip, dmg, grav)( (Entity) {.id = i, .pos = (SDL_FRect) {.x = 50, .y = 680, .w = 90, .h = 120}, .src = &(SDL_Rect){.x=i*4*600, .y=0, .w=600, .h =800}, .timer = {0,0,0}, .components = {hp, state, flip, dmg, grav}} )

typedef struct Entity{
    unsigned char id;
    char components[COMPONENT_MAX];
    SDL_Rect* src;
    SDL_FRect pos;
    Uint32 timer[TIMER_MAX];
}Entity;

float timerMax[TIMER_MAX] = {2.5, 0.5, 1}; // NOTE: Adjust these values
int current_world_size = 1;

Entity world[50] = {
    // ID, HP, Flip, Damage, Speed, Gravity
    entity(plr, IDLE, 3, 1, 1, 1),
    //entity(DK, 25, -1, 1, 20, 1),
};

Entity presets[19] = {
    entity(DK, ATK, 1, 0, 1, 0), // DEBUG
};

void Shoot(int caller, int idx){
    world[current_world_size] = presets[idx-1];
    world[current_world_size].pos = world[caller].pos;
    world[current_world_size].components[FLIPPED] = world[caller].components[FLIPPED]; //TODO: might change speed flipped to + & - speeds
    world[current_world_size].timer[SPECIAL-1] = SDL_GetTicks();
    world[current_world_size++].pos.x += world[caller].components[FLIPPED] * 10;
    world[caller].timer[0] = SDL_GetTicks();
    printf("Spawned object");
}

void UpdateTimers(int i){
    for (int x = 0; x < TIMER_MAX; x++){
        if (world[i].timer[x] > 0 && (float) ((SDL_GetTicks() - world[i].timer[x])) / 1000 >= timerMax[x])
            world[i].timer[x] = 0;
    }
}

void handleAI(int caller){
    for (int i = 0; i < TIMER_MAX; i++){
        if (!world[caller].timer[i]){
            world[caller].timer[i] = SDL_GetTicks();
            switch(i+1){
                case SHOOT: // Shoot(caller, 0); //TODO: find a system for monkey specific projectile ids
                    break;
                case ATK: world[caller].components[ANIMATION] = ATK;
                    break;
                case SPECIAL:
                          continue;
                    switch(world[caller].id){
                        case plr: break;
                        case DK:
                            break;
                        case Kranky:
                            break;
                        case Leo:
                            break;
                        case Drake:
                            break;
                        default: world[caller] = world[current_world_size--]; // Delete 
                            break;
                    }
                    break;
            }
        }
    }
}

void handleAIMovement(int caller){
    switch(world[caller].id){
        case plr: break;
        //case DK: break;
        case Kranky: break;
        case Drake: break;
        default: world[caller].pos.x += 0.25 * world[caller].components[FLIPPED];
            break;
    }
}

void Die(int idx, int* gameState, int* menuState){
    if (world[idx].id == plr){
        *gameState = PAUSED;
        *menuState = GAME_OVER;
    } else world[idx] = world[current_world_size--]; 
}

void UpdateWorld(int* gameState, int* menuState){
    for (int i = 0; i < current_world_size; i++){
        world[i].pos.y += (world[i].components[GRAVITY]) * Gravity;
        
        // Handle Collision
        if (world[i].pos.x < 0)                  world[i].pos.x = 0;
        else if (world[i].pos.x > 1048 - world[i].pos.w) world[i].pos.x = 1048 - world[i].pos.w; // Screen width
        
        if (world[i].pos.y < 0) world[i].pos.y = 0;
        else if (world[i].pos.y > 680 - world[i].pos.h) world[i].pos.y = 680 - world[i].pos.h; // Screen width

        UpdateTimers(i);
        handleAIMovement(i);
        handleAI(i); // Handle the variation in logic

        // Handle Damage
        for (int x = i+1; x < current_world_size; x++){
            if ( bounds_check(world[i].pos, world[x].pos) && world[x].components[ANIMATION] == ATK ){
                world[i].components[HP] -= world[x].components[DAMAGE];
                if (world[i].components[HP] < 0) Die(i, gameState, menuState);
            }
        }
    }
}
