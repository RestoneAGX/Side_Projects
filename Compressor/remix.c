#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLIDER_LEN 0xFF

FILE *fp;
FILE *outputFP;

void ProcessData(int Phase){
    char slider[SLIDER_LEN];
    unsigned char skipping;

    unsigned char has_space = 0;
    unsigned char count;

    unsigned char idx = 0;

    if (Phase){ // Phase 1 Processing
        while (!feof(fp)){
            slider[idx] = fgetc(fp);
            if (slider[idx] == '#') skipping = 1;
            if (skipping){
                skipping = slider[idx] != '\n';
                continue;
            }

            if (slider[idx] == ' ' || slider[idx] == '\n'){
                if (!has_space)  has_space = 1;
                else {
                    char original_char = slider[idx];
                    slider[idx] = 0;
                    int x_size = 4;

                    printf("word: %s, ", slider+idx-count);

                    if ( slider[idx-count+1] == '.' || slider[idx-count+2] == '.' ) {
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
                    count = 0;
                }
                if (slider[idx] == '\n'){
                    fwrite(slider, 1, idx, outputFP);
                    idx = 0;
                    continue;
                }
            } else count++;

            idx++;
        }
    } else {}     // Phase 2 Processing | TODO: Implement Phase 2 Processing
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
