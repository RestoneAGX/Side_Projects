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
#define Gravity 0.1

// Tools
#define bounds_check(pos1,pos2)( !(pos1.x < pos2.x || pos1.x + pos1.w > pos2.x || pos1.y < pos2.y ||  pos1.y + pos1.h > pos2.y) )

#define entity(i, xOff, state, hp, flip, dmg, grav)( (Entity) {.id = i, .pos = (SDL_FRect) {.x = xOff, .y = 580, .w = 90, .h = 120}, .src = &(SDL_Rect){.x=i*4*600, .y=0, .w=600, .h =800}, .timer = {0,0,0}, .components = {hp, state, flip, dmg, grav}} )

typedef struct Entity{
    unsigned char id;
    char components[COMPONENT_MAX];
    SDL_Rect* src;
    SDL_FRect pos;
    Uint32 timer[TIMER_MAX];
}Entity;

float timerMax[TIMER_MAX] = {1, 1.2, 5}; // NOTE: Adjust these values
int current_world_size = 2;

Entity world[50] = {
    // ID, State, HP, Flip, Damage, Gravity
    entity(plr, 50, IDLE, 3, 1, 1, 1),
    entity(Leo, 1000, ATK, 25, -1, 1, 1),
};

Entity presets[19] = {
    entity(DK, 1000, ATK, 1, 0, 1, 0), // DEBUG
};

void Shoot(int caller, int idx){
    world[current_world_size] = presets[idx-1];
    world[current_world_size].pos = world[caller].pos;
    world[current_world_size].components[FLIPPED] = world[caller].components[FLIPPED]; //TODO: might change speed flipped to + & - speeds
    
    world[current_world_size].timer[SHOOT-1] = 0xFFFFFFFF;
    world[current_world_size].timer[ATK-1]   = 0xFFFFFFFF;
    world[current_world_size].timer[SPECIAL-1] = SDL_GetTicks();
    
    world[current_world_size++].pos.x += world[caller].components[FLIPPED] * 10;
    world[caller].timer[0] = SDL_GetTicks();
}

void UpdateTimers(int i){
    for (int x = 0; x < TIMER_MAX; x++){
        if (world[i].timer[x] > 0 && world[i].timer[x] < 0xFFFFFFFF && (float) ((SDL_GetTicks() - world[i].timer[x])) / 1000 >= timerMax[x]) {
            world[i].timer[x] = 0;
            printf("Timer %d Cleared for : %d, current_world_size: %d\n", x, i, current_world_size);
        }
    }
}

//DEBUG: Test 0.1 
#define AI_MOVE_SPEED 0.25
// DEBUG: 10
#define AI_STOPPING_DIST 10

void handleAIMovement(int caller){
    switch(world[caller].id){
        case plr: break;
        case DK:
            world[caller].pos.x += AI_MOVE_SPEED * world[caller].components[FLIPPED]; 
            if (abs(world[0].pos.x - world[caller].pos.x) < AI_STOPPING_DIST)
                world[caller].pos.x -= AI_MOVE_SPEED * world[caller].components[FLIPPED];
            break;
        case Kranky: world[caller].pos.x += AI_MOVE_SPEED * world[caller].components[FLIPPED];
            break;
        case Leo: break;
        case Drake: world[caller].pos.x += AI_MOVE_SPEED * world[caller].components[FLIPPED];
            world[caller].pos.y += AI_MOVE_SPEED * world[caller].components[ANIMATION];
            break;
        default: world[caller].pos.x += 0.25 * world[caller].components[FLIPPED];
            break;
    }
}

void handleAI(int caller){
    if (caller == plr) return;

    for (int i = 0; i < TIMER_MAX; i++){
        if (world[caller].timer[i] == 0){
            world[caller].timer[i] = SDL_GetTicks();
            switch(i+1){
                case SHOOT: 
                    Shoot(caller, 1); //REPLACE: 0 with a value based on the id of the caller exa: caller.id + Drake
                    if (world[caller].id == Kranky) world[current_world_size-1].pos.y -= 100; // REPLACE: 10 after tuning
                    break;
                case ATK: world[caller].components[ANIMATION] = ATK;
                    switch(world[caller].id){
                        case DK: break;
                        case Kranky: break;
                        case Leo: break;
                        case Drake: break;
                    }
                    break;
                case SPECIAL:
                    switch(world[caller].id){
                        case DK: break;  //DEBUG: Re-enable
                        case Kranky: world[caller].components[FLIPPED] *= -1;
                            break;
                        case Leo: Shoot(caller, 0); //REPLACE 0 with leo's lightning 
                            break;
                        case Drake:
                            break;
                        default: world[caller] = world[current_world_size--]; // Delete Obj
                            break;
                    }
                    break;
            }
        }
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
        handleAI(i);

        // Handle Damage
        for (int x = i+1; x < current_world_size; x++){
            if ( bounds_check(world[i].pos, world[x].pos) ){
                world[i].components[HP] -= world[x].components[DAMAGE];
                if (world[i].components[HP] < 0 || world[i].id > Drake) Die(i, gameState, menuState);
            }
        }
    }
}
