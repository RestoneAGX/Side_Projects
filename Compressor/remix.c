#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc < 2) return -1;
    FILE *fp = fopen(argv[2], "r+");

    char slider[100];
    unsigned char skipping;

    unsigned char has_space = 0;
    unsigned char count;
    unsigned char isFloat;
    unsigned char numBuffer[8];

    unsigned char idx;
    char c;

    while (!feof(fp)){
        c = fgetc(fp);
        // if # -> skip UNTIL '\n'
        if (c == '#')skipping = 1;
        if (c == '\n') skipping = 0;
        if (skipping) continue;
        
        if (has_space){
            // isFloat = (c == '.') ^ isFloat
            if (c == '.') isFloat = 1;
            else if (c == ' '){
                // if (count == 1)
                has_space = 0;
                memcpy(numBuffer, slider+idx-count, count);
                numBuffer[count+1] = 0;
                unsigned int x = (isFloat) ? atof(numBuffer) : atoi(numBuffer);
                int x_size = (isFloat) ? 4 : (x >= 127) + 1; 
                // estimate size of val, based on conversion
                // write over the line memory
                memcpy(slider+(idx-count), &numBuffer, x_size);
            }
            count++;
        }
        if (c == ' ') has_space = 1;

        // check space, if new space check UNTIL space again
        // if 2 spaces found or space until \n
            // while searching
                // count the bytes
                // check for '.'
            // Convert the val, if float, flag check, convert to float
            // if val is not num, skip
            // else overwrite base with conversion
    }

    return 0;
}
