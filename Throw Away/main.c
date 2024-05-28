#include<stdio.h>

typedef struct{
    int x, y;
    int hp;
    unsigned char state; // 0 = vulnerable = yellow, 1 = attack = red, 2 = blue = green
} player;

#define INPUT_SIZE 3

char input[INPUT_SIZE];

void move(player *plr){
    scanf("%s",input);
    for (int i = 0; i < INPUT_SIZE; i++){
        switch (input[i]) {
            case 'w':
            plr->y -= 1;
            break;

            case 'a':
            plr->x -= 1;
            break;

            case 's':
            plr->y += 1;
            break;

            case 'd':
            plr->x += 1;
            break;

            case 'z':
            plr->state = 0;
            break;
            case 'x':
            plr->state = 1;
            break;
            case 'c':
            plr->state = 2;
            break;

            default:
            break;
        }
    }
}

void world_check(){}

int main(){
    player plr = {12,0,0,0};
    
    while (1){
        printf("\x1B[%d;%dH XXX", plr.x, plr.y);
        move(&plr);
    }
    return 0;
}
