#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SLIDER_LEN 0xFF

FILE* fp;
FILE* outputFP;

void ProcessData(int phase){
    char slider[SLIDER_LEN];
    unsigned char skipping;
    unsigned char hasSpace = 0;
    unsigned char isFloat = 0;
    unsigned char idx = 0;
    unsigned char count;
    
    if (phase){ // Phase 1 Processing
        while(!feof(fp)){
            slider[idx] = fgetc(fp);
            switch(slider[idx]){
                case '#': skipping = 1;
                break;
                case '.': isFloat = 1;
                case ' ':
                    conversions: 
                    if (hasSpace){
                        //if(slider[idx-count] > 57) goto Clean_Line;
                        char ogChar = slider[idx];
                        int x_size = 4;
                        slider[idx] = 0;
                        
                        if (isFloat) {
                            float x = atof(slider+idx-count);
                            memcpy(slider+idx-count, &x, x_size);
                        }else{
                            int x = atoi(slider+idx-count);
                            x_size = (x > 127) + 1;
                            memcpy(slider+idx-count, &x, x_size);
                        }
                        
                        if (ogChar == '\n') goto Clean_Line;
                        idx -= count - x_size;
                        slider[idx] = ' ';
                        hasSpace = 0;
                        isFloat = 0;
                    }else{
                        hasSpace = 1;
                        count = 0;
                    }
                break;
                case '\n':
                    if (hasSpace) goto conversions;
                    Clean_Line:
                        slider[idx] = '\n'; // NOTE: This is done just in-case the GOTO has brought us back here
                        if (!skipping) fwrite(slider, idx, 1, outputFP);
                        hasSpace = 0;
                        skipping = 0;
                        isFloat = 0;
                        idx = 0;
                break;
                default: count++;
                break;
            }
        }
    }
    else{} // Phase 2 Processing | TODO: Implement Phase 2
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
