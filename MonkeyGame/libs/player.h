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
    SHEILD,
    SHOOTING,
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

enum GameStates{
    QUIT,
    ACTIVE,
    PAUSED,
};

// Tools
#define bounds_check(pos1,pos2)( !(pos1.x < pos2.x || pos1.x + pos1.w > pos2.x + pos2.w || pos1.y < pos2.y ||  pos1.y + pos1.h > pos2.y + pos2.h) )
#define dist(spriteA, spriteB) (sqrt(                               \
    ( (spriteB.x - spriteA.x) * (spriteB.x - spriteA.x) ) + \
    ( (spriteB.y - spriteA.y) * (spriteB.y - spriteA.y) ) ) * 0.1)


typedef struct Entity{
    unsigned char id;
    char components[6];
    SDL_Rect* src;
    SDL_FRect pos;
}Entity;

// 0 plr, 1 boss, others projectiles
int current_world_size = 1;

Entity world[20] = {
    (Entity){plr, {}},
};

Entity presets[19] = {
};

SDL_Texture *atlas;

int gravity = 10;

void Shoot(int caller, int idx){
    world[caller].components[ANIMATION] = SHOOTING;
    world[current_world_size] = presets[idx-1];
    world[current_world_size].pos = world[caller].pos;
    world[current_world_size].components[FLIPPED] = world[caller].components[FLIPPED];
    world[current_world_size++].pos.x += world[caller].components[FLIPPED] * 5;
}

void loadTextures(SDL_Renderer* renderer){
    SDL_Surface* preop = SDL_LoadBMP("./atlas.bmp");
    SDL_Surface* oped = SDL_ConvertSurface(preop, preop->format, 0);
    atlas = SDL_CreateTextureFromSurface(renderer, oped);
    SDL_FreeSurface(preop);
    SDL_FreeSurface(oped); 
}

void handleInput(SDL_Event *event, int* gameActive, int* input){
    while(SDL_PollEvent(event)){
        switch(event->type){
            case SDL_QUIT: *gameActive = QUIT;
            break;

            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT)
                    Shoot(plr, Kɔbe);
                else
                    world[plr].components[ANIMATION] = SHEILD;
                break;
            
            case SDL_MOUSEBUTTONUP:
                if (event->button.button == SDL_BUTTON_RIGHT)
                    world[plr].components[ANIMATION] = IDLE;
                break;

            case SDL_KEYDOWN:
                switch(event->key.keysym.scancode){
                    case SDL_SCANCODE_A: input[0] = 1;
                         world[plr].components[FLIPPED] = -1;
                    break;
                    case SDL_SCANCODE_D: input[0] = -1;
                         world[plr].components[FLIPPED] = 1;
                    break;
                    case SDL_SCANCODE_W: input[1] = 1;
                    break;
                    case SDL_SCANCODE_S: input[1] = -1;
                    break;
                    case SDL_SCANCODE_SPACE: Shoot(plr, Banana);
                    break;
                    case SDL_SCANCODE_ESCAPE:
                    *gameState = (ACTIVE) ? PAUSED : ACTIVE;
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
                    case SDL_SCANCODE_W: input[1] = 0;
                    break;
                    case SDL_SCANCODE_S: input[1] = 0;
                    break;
                    default: break;
                }
            break;
        }
    }
}

void handlePlayerMovement(int* input){
    world[plr].pos.x += input[0] * 5;
    world[plr].pos.y += input[1] * 5;
}

void RenderWorld(SDL_Renderer* renderer){
    // TODO: Render background
    for (int i = 0; i < current_world_size; i++){
        world[i].src->x += world[i].id + world[i].components[ANIMATION]; 
        SDL_RenderCopyExF(renderer, atlas, world[i].src, &world[i].pos, 0, NULL, SDL_FLIP_HORIZONTAL * world[i].components[FLIPPED]);
    }
}

void handleAI(int caller){
    switch(world[caller].id){
        case DK:
            break;
        case Kranky:
            break;
        case Leo:
            break;
        case Drake:
            break;
        case Banana: // TODO: add slippage/stun
            break;
    }
}

void Die(int idx){
    switch(world[idx].id){
        case plr: //TODO: GameOver // 0 is the Player
            break;
        // cases 1-5 are bosses
        default: world[current_world_size--] = world[idx]; // These are normally used for projectiles and particle FX
            break;
    }
}

void UpdateWorld(){
    for (int i = 0; i < current_world_size; i++){
        world[i].pos.y -= (world[i].components[GRAVITY]) * gravity;
        world[i].pos.x += (world[i].id > 0) * world[i].components[SPEED] * world[i].components[FLIPPED];

        // Handle Collision
        if (world[i].pos.x < 0)                  world[i].pos.x = 0;
        if (world[i].pos.x > 1048 - world[i].pos.w) world[i].pos.x = 1048 - world[i].pos.w; // Screen width
        if (world[i].pos.y < 0)                  world[i].pos.y = 0;
        if (world[i].pos.y > 680 - world[i].pos.h)  world[i].pos.y = 680 - world[i].pos.h; // Screen width

        handleAI(i);

        // Handle Damage
        for (int x = i+1; x < current_world_size; i++){
            if ( bounds_check(world[i].pos, world[x].pos) && world[x].components[ANIMATION] == ATK && world[i].components[ANIMATION] != SHEILD ){
                world[i].components[HP] -= world[x].components[DAMAGE];
                if (world[i].components[HP] < 0) Die(i);
            }
        }
    }
}
