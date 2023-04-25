#include<stdio.h>
#include<stdlib.h>

#define OR(slot, a,b,c)(slot[a] | slot[b] | slot[c])

char slots[9] = {'1','2','3','4','5','6','7','8','9'};
char plr = 'X';

int checkForWin(char plr, int* slot){
    return (OR(slot, 0, 1, 2) == plr) || (OR(slot, 0, 4, 8) == plr) || (OR(slot, 0, 3, 6) == plr) ||
           (OR(slot, 2, 5, 8) == plr) || (OR(slot, 2, 4, 6) == plr) || 
           (OR(slot, 6, 7, 8) == plr) || (OR(slot, 1, 4, 7) == plr) || (OR(slot, 3, 4, 5) == plr);
}

int main(){
    printf("Welcome To Tic-Tac-Toe\nType the number to select your spot & press q to quit\n\n");
    unsigned char gameActive = 1;
    char input[2] = {0,0};
    while(gameActive){
        printf("-------------\n| %c | %c | %c |\n\n| %c | %c | %c |\n\n| %c | %c | %c |\n\n Player: %c\n", slots[0], slots[1], slots[2], slots[3], slots[4], slots[5], slots[6], slots[7], slots[8], plr);
        input[0] = getc(stdin);
        printf(input);
        int point = atoi(input);
        
        if (point < 1){
            printf("Not valid input\n\n");
            continue;
        }

        if(slots[point-1] != 'X' && slots[point-1] != 'O'){
            plr = (plr == 'X') ? 'O' : 'X';
            slots[point-1] = plr;
        }
        
        if (checkForWin(plr, slots)){
            printf("\n%c Wins!!!\n", plr);
            return 0;
        }
    }
    return 0;
}
