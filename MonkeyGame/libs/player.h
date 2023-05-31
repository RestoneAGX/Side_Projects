#include"Systems.h"

float calcVel = 0;

void handlePlayerMovement(int* input){
    if ( world[0].components[DAMAGE] ) calcVel += 0.0005;

    world[plr].pos.x += input[0] * 0.05;
    world[plr].pos.y -= calcVel;
    
    if ( calcVel > 0.5){
        calcVel = 0;
        world[0].components[DAMAGE] = 0;
    }
    // printf("Calc Vel: %f\n", calcVel);
}

void handleInput(SDL_Event *event, int* gameState, int* input){
    while(SDL_PollEvent(event)){
        switch(event->type){
            case SDL_QUIT: *gameState = QUIT;
            break;

            case SDL_MOUSEBUTTONDOWN: 
                if(event->button.button == SDL_BUTTON_LEFT){
                    if (world[plr].timer[0] == 0)Shoot(plr, DK); // DEBUG: replace with Kɔbe
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
                    case SDL_SCANCODE_ESCAPE:
                    *gameState = (*gameState == ACTIVE) ? PAUSED : ACTIVE;
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
