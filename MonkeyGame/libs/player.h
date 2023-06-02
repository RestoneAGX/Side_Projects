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

void SetStage(int enemy){
    current_world_size = 2;
    world[1] = preset[0];
    world[1].id = enemy;
    world[1].pos.x = 1000;
    world[1].pos.y = 560;

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
                    if(world[0].timer[0] == 0) Shoot(plr, DK); // DEBUG: replace with Kɔbe
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
                    case SDL_SCANCODE_0: SetStage(DK);
                    break;
                    case SDL_SCANCODE_1: SetStage(Kranky);
                    break;
                    case SDL_SCANCODE_2: SetStage(Leo);
                    break;
                    case SDL_SCANCODE_3: SetStage(Drake);
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
