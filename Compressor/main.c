#include <stdio.h>

int main(int argc, char** argv){
    if (argc < 2) return -1;

    FILE* fp = fopen(argv[2], "r+");

    char slider[25];
    char output[1000];

    unsigned char skipping;
    unsigned char skips;
    unsigned char last_space;
    unsigned char has_space;

    int i = 0, point = 0;
    while (!feof(fp)) {
        char c = fgetc(fp);
        if (c == '#'){ 
            skipping = 1;
            skips = 0xFF;
        }
        else if (c == '\n') {
            i = 0;
            // numStart = i; // set out num start to current idx
            // skips = 3; //then skip 3 iterations
        }
        // skips -= skipping;
        // if (skips == 0) skipping = 0;
        if (skipping) continue;
        if (c == ' ')
            if (has_space)
                // loop back until last space
            else
                last_space = i;
        // Check if space
            // check if next space is a letter
            // if letter skipp the lin
    }
    return 0;
}