#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLIDER_LEN 0xFF

FILE *fp;
FILE *outputFP;

int ProcessData(int Phase){
    char slider[SLIDER_LEN];
    unsigned char skipping;

    unsigned char has_space = 0;
    unsigned char count;
    unsigned char isFloat;

    unsigned char idx = 0;

    if (Phase){ // Phase 1 Processing
        while (!feof(fp)){
        slider[idx] = fgetc(fp);
        if (slider[idx] == '#') skipping = 1;  // if # -> skip UNTIL '\n'
        else if (skipping && slider[idx] == '\n' || slider[idx] < 1 || (int)idx == SLIDER_LEN){
            fwrite(slider, idx, 1, outputFP);
            has_space = 0;
            skipping = 0;
            idx = 0;
        }
        if (skipping) continue;
      
        if (has_space){
            if (slider[idx] == '.') isFloat = 1;  // isFloat = (c == '.') ^ isFloat
            else if (slider[idx] == ' ' || slider[idx] == '\n'){
                char original_char = slider[idx];
                slider[idx] = 0;
                int x_size = 4;

                printf("word: %s, ", slider+idx-count);

                if (isFloat) {
                    float x = atof(slider+idx-count); // TODO: Add float16 conversion
                    memcpy(slider+idx-count, &x, x_size);
                } else {
                    int x = atoi(slider+idx-count);
                    x_size = (x > 127) + 1;
                    memcpy(slider+idx-count, &x, x_size);
                }

                idx -= count - x_size;
                printf("count: %d idx_char: %c\n", count, slider[idx]);
                slider[idx] = original_char;

                has_space = 0;
                isFloat = 0;
                count = -1;
            }
            count++;
        }
        if (slider[idx++] == ' ') has_space = 1;
    }
    }else{      // Phase 2 Processing | TODO: Implement Phase 2 Processing
    }
}

int main(int argc, char** argv){
    if (argc < 2) return -1;

    fp = fopen(argv[1], "r+");
    outputFP = fopen("tempOutput.Robj","w");

    ProcessData(1); // Phase 1

    ProcessData(0); // Phase 2

    fclose(fp);
    fclose(outputFP);

    return 0;
}
