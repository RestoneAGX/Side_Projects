#pragma once
#include<SDL2/SDL.h>

enum Components{
    HP,
    ANIMATION,
    FLIPPED,
    DAMAGE,
    SPEED,
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
    Banana,
    Kɔbe
};

// Constants
#define COMPONENT_MAX 6
#define TIMER_MAX 3
#define Gravity 0.025

// Tools
#define bit_check(v, i) ((v & (1<<i)))
#define bit_clear(v, i) (v = v & ~(1<<i))
#define bit_set(v, i) (v = v | (1<<i))

#define bounds_check(pos1,pos2)( !(pos1.x < pos2.x || pos1.x + pos1.w > pos2.x + pos2.w || pos1.y < pos2.y ||  pos1.y + pos1.h > pos2.y + pos2.h) )

#define entity(i, hp, flip, dmg, spd, grav)( (Entity) {.id = i, .pos = (SDL_FRect) {.w = 90, .h = 120}, .src = &(SDL_Rect){.x=i*600, .y=i*800, .w=600, .h =800}, .timer = {0,0,0}, .components = {hp, IDLE, flip, dmg, spd, grav}} )

typedef struct Entity{
    unsigned char id;
    unsigned char cooldowns; // 0 is for movement, the reset are the animations
    char components[COMPONENT_MAX];
    SDL_Rect* src;
    SDL_FRect pos;
    Uint32 timer[TIMER_MAX];
}Entity;

float timerMax[TIMER_MAX] = {0.25, 0.5, 0.2}; // NOTE: Adjust this values
int current_world_size = 1;

Entity world[50] = {
    entity(plr, 3, 1, 1, 1, 1),  
};

Entity presets[19] = {
};

void Shoot(int caller, int idx){
    world[current_world_size] = presets[idx-1];
    world[current_world_size].pos = world[caller].pos;
    world[current_world_size].components[FLIPPED] = world[caller].components[FLIPPED];
    world[current_world_size].pos.x += world[caller].components[FLIPPED] * 10;
    bit_set(world[current_world_size].cooldowns, SHOOT);
    ++current_world_size;
}

void UpdateTimers(int i){
    for (int x = 0; x < TIMER_MAX; x++){
        if (bit_check(world[i].cooldowns, x)) world[i].timer[x] = SDL_GetTicks();
        else if ((float) (SDL_GetTicks() - world[i].timer[x]) / 1000 >= timerMax[x]){
            bit_clear(world[i].cooldowns, x);
            world[i].timer[x] = 0;
        }
    }
}

void handleAI(int caller){
    for (int i = 0; i < TIMER_MAX+1; i++){
        if (!bit_check(world[caller].cooldowns, i)){
            bit_set(world[caller].cooldowns,i);
            switch(i+1){
                case SHOOT: Shoot(caller, 0); //TODO: find a system for monkey specific projectile ids
                    break;
                case ATK: world[caller].components[ANIMATION] = ATK;
                    break;
                case SPECIAL:
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
                        default: world[caller] = world[current_world_size--]; // Delete projectiles
                            break;
                    }
                    break;
                default: //MOVEMENT
                    bit_clear(world[caller].cooldowns, i);
                    switch(world[caller].id){
                        case plr: break;
                        case DK: break;
                        case Kranky: break;
                        case Drake: break;
                        default: world[i].pos.x += world[i].components[SPEED] * world[i].components[FLIPPED];
                            break;
                    }
                    break;
            }
        }
    }
}

void Die(int idx){
    switch(world[idx].id){
        case plr: //TODO: GameOver // 0 is the Player
            break;
        // cases 1-5 are bosses
        default: world[idx] = world[current_world_size--]; // These are normally used for projectiles and particle FX
            break;
    }
}

void UpdateWorld(){
    for (int i = 0; i < current_world_size; i++){
        world[i].pos.y += (world[i].components[GRAVITY]) * Gravity;

        // Handle Collision
        if (world[i].pos.x < 0)                  world[i].pos.x = 0;
        else if (world[i].pos.x > 1048 - world[i].pos.w) world[i].pos.x = 1048 - world[i].pos.w; // Screen width
        
        if (world[i].pos.y < 0) world[i].pos.y = 0;
        else if (world[i].pos.y > 680 - world[i].pos.h) world[i].pos.y = 680 - world[i].pos.h; // Screen width
        
        return;

        UpdateTimers(i);

        // handleAI(i); // TO-FIX: crashes the game

        // Handle Damage
        for (int x = i+1; x < current_world_size; i++){
            if ( bounds_check(world[i].pos, world[x].pos) && world[x].components[ANIMATION] == ATK ){
                world[i].components[HP] -= world[x].components[DAMAGE];
                if (world[i].components[HP] < 0) Die(i);
            }
        }
    }
}
