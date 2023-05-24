#include<SDL2/SDL.h>

// Components
#define HP 0
#define ANIMATION 1
#define FLIPPED 2
#define DAMAGE 3
#define GRAVITY 4

// Animation Types
#define IDLE 0
#define SHIELD 1
#define ATK 2
#define SHOOTING 3

// Tools
#define bounds_check(pos1,pos2)( !(pos1.x < pos2.x || pos1.x + pos1.w > pos2.x + pos2.w || pos1.y < pos2.y ||  pos1.y + pos1.h > pos2.y + pos2.h) )
#define dist(spriteA, spriteB) (sqrt(                               \
    ( (spriteB.x - spriteA.x) * (spriteB.x - spriteA.x) ) + \
    ( (spriteB.y - spriteA.y) * (spriteB.y - spriteA.y) ) ) * 0.1)


typedef struct Entity{
    unsigned char id;
    unsigned char components[5];
    SDL_Rect* src;
    SDL_FRect pos;
}Entity;

// 0 plr, 1 boss, others projectiles
int current_world_size = 2;

Entity world[20] = {
    (Entity){0, {}},
};

Entity presets[19] = {
};

SDL_Texture *atlas;

int gravity = 10;

void Shoot(int idx){
    world[current_world_size] = presets[idx-1];
    world[current_world_size].pos = world[0].pos;
    world[current_world_size++].pos.x += world[0].components[0] * 5;
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
            case SDL_QUIT: *gameActive = 0;
            break;

            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT)
                    Shoot(2);
                else
                    world[0].components[ANIMATION] = 1;
                break;
            
            case SDL_MOUSEBUTTONUP:
                if (event->button.button == SDL_BUTTON_RIGHT){
                    world[0].components[ANIMATION] = 0;
                }
                break;

            case SDL_KEYDOWN:
                switch(event->key.keysym.scancode){
                    case SDL_SCANCODE_A: input[0] = 1;
                    break;
                    case SDL_SCANCODE_D: input[0] = -1;
                    break;
                    case SDL_SCANCODE_W: input[1] = 1;
                    break;
                    case SDL_SCANCODE_S: input[1] = -1;
                    break;
                    case SDL_SCANCODE_SPACE: Shoot(3); // Banana Peel
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

void renderWorld(SDL_Renderer* renderer){
    // TODO: Render background
    for (int i = 0; i < current_world_size; i++){
        world[i].src->x += world[i].id + world[i].components[ANIMATION]; 
        SDL_RenderCopyExF(renderer, atlas, world[i].src, &world[i].pos, 0, NULL, SDL_FLIP_HORIZONTAL * world[i].components[FLIPPED]);
    }
}

void UpdateWorld(){
    for (int i = 0; i < current_world_size; i++){
        world[i].pos.y -= (world[i].components[GRAVITY]) ? gravity : 0;

        // Handle Collision
        if (world[i].pos.x < 0)                  world[i].pos.x = 0;
        if (world[i].pos.x > 1048 - world[i].pos.w) world[i].pos.x = 1048 - world[i].pos.w; // Screen width
        if (world[i].pos.y < 0)                  world[i].pos.y = 0;
        if (world[i].pos.y > 680 - world[i].pos.h)  world[i].pos.y = 680 - world[i].pos.h; // Screen width

        // Handle Combat
        for (int x = i+1; x < current_world_size; i++){
            if ( bounds_check(world[i].pos, world[x].pos) && world[x].components[ANIMATION] == ATK && world[i].components[ANIMATION] != SHIELD )
                world[i].components[HP] -= world[x].components[DAMAGE];
        }
    }
}
