#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLIDER_LEN 50

FILE *fp;
FILE *outputFP;

int main(int argc, char** argv){
    if (argc < 2) return -1;

    fp = fopen(argv[1], "r+");
    outputFP = fopen("output.Robj","w");
    
    char slider[SLIDER_LEN];
    unsigned char skipping;

    unsigned char has_space = 0;
    unsigned char count;
    unsigned char isFloat;
    unsigned char numBuffer[10];

    unsigned char idx = 0;

    // Phase 1 | TODO: Wrap into a function
    while (!feof(fp)){
        slider[idx] = fgetc(fp);
        if (slider[idx] == '#') skipping = 1;  // if # -> skip UNTIL '\n'
        else if (slider[idx] == '\n' || slider[idx] < 1 || idx == SLIDER_LEN){
            fwrite(slider, idx, 1, outputFP);
            has_space = 0;
            skipping = 0;
            idx = 0;
        }
        if (skipping) continue;
      
        if (has_space){
            if (slider[idx] == '.') isFloat = 1;  // isFloat = (c == '.') ^ isFloat
            else if (slider[idx] == ' ' || slider[idx] == '\n'){
                // if (count == 1)
                // memcpy(numBuffer, &slider[idx-count], count);
                // numBuffer[count+1] = 0;
                
                slider[idx] = 0;
                int x_size = 4;

                printf("word: %s, ", slider+idx-count);

                if (isFloat) {
                    // TODO: Add float16 conversion
                    float x = atof(slider+idx-count);
                    memcpy(slider+idx-count, &x, x_size);
                } else {
                    int x = atoi(slider+idx-count);
                    x_size = (x > 127) + 1;
                    memcpy(slider+idx-count, &x, x_size);
                }

                // idx -= count - (x_size - 1);
                // idx += -count + x_size + 1;
                printf("count: %d\n", count);
                slider[idx] = ' ';

                isFloat = 0;
                count = -1;
            }
            count++;
        }
        if (slider[idx++] == ' ') has_space = 1;
    }

    // TODO: Phase 2

    fclose(fp);
    fclose(outputFP);

    return 0;
}
