#include"Systems.h"

#define Gravity 0.1

float calcVel = 0;

void handlePlayerMovement(int* input){
    if ( world[0].components[DAMAGE] ) calcVel += 0.001;

    world[plr].pos.x += input[0] * 0.05;
    world[plr].pos.y -= calcVel;
    
    if ( calcVel > 0.75 ){
        calcVel = 0;
        world[0].components[DAMAGE] = 0;
    }

    world[plr].pos.y += Gravity;
    // printf("Calc Vel: %f\n", calcVel);
}

void SetStage(unsigned char enemy){
    current_world_size = 2;

    world[1] = (Entity){.id = enemy, .components = {25, ATK, -1, 1}, .src = srcs+(int)enemy, .pos = {.x = 1000, .y = 560, .w = 90, .h = 120}, .timer = {0,0,0}};
    printf("Boss ID: %d\n", world[1].id);

    world[plr].pos.x = 50;
    world[plr].pos.y = 560;
}

void handleInput(SDL_Event *event, int* gameState, int* input){
    while(SDL_PollEvent(event)){
        switch(event->type){
            case SDL_QUIT: *gameState = QUIT;
            break;

            case SDL_MOUSEBUTTONDOWN: 
                if(event->button.button == SDL_BUTTON_LEFT){
                    if(world[0].timer[0] == 0){
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        char isFlipped = (((int)(world[plr].pos.x - (float)x)) & (1 << 31)) >> 31;
                        Shoot( plr, Kɔbe, (isFlipped) ? 1 : -1);
                    }
                } else world[0].components[DAMAGE] = 1;
            break;

            case SDL_KEYDOWN:
                switch(event->key.keysym.scancode){
                    case SDL_SCANCODE_A: input[0] = -1;
                        world[plr].components[FLIPPED] = -1;
                    break;
                    case SDL_SCANCODE_D: input[0] = 1;
                        world[plr].components[FLIPPED] = 1;
                    break;
                    case SDL_SCANCODE_SPACE:
                        if(world[0].timer[0] == 0){
                            Shoot(plr, Kɔbe, world[plr].components[FLIPPED]);
                        }
                    break;
                    case SDL_SCANCODE_1: SetStage(DK);
                    break;
                    case SDL_SCANCODE_2: SetStage(Kranky);
                    break;
                    case SDL_SCANCODE_3: SetStage(Leo);
                    break;
                    case SDL_SCANCODE_4: SetStage(Drake);
                    break;
                    default: break;
                }
            break;

            case SDL_KEYUP:
                switch(event->key.keysym.scancode){
                    case SDL_SCANCODE_A: input[0] = 0;
                    break;
                    case SDL_SCANCODE_D: input[0] = 0;
                    break;
                    default: break;
                }
            break;
        }
    }
}
