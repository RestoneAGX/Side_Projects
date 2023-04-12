#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SLIDER_LEN 0xFF

FILE *fp;
FILE *outputFP;

inline void Process(){
    char slider[SLIDER_LEN];
    char temp[SLIDER_LEN];
    char mode; // set the value = to current letter
    int idx = 0;

    while (!feof(fp)){
        slider[idx] = fgetc(fp);
        if (slider[idx] == '\n') {
            int space_idx = 0;
            mode = slider[0];
            
            if ( slider[0] == '#' || slider[0] == '\n' ) continue;
            else if ( slider[0] != 'm' && slider[0] != 'u' ){
                for ( int i = 1; i < idx; i++ )
                    if ( slider[i] == ' ' ) {
                        if ( space_idx == 0 ) space_idx = i;
                        else {
                            slider[i] = 0;
                            int x_size = 4;
                            if ( slider[space_idx+2] == '.' || slider[space_idx+3] == '.' ) {
                                float x = atof( slider+space_idx+2 ); // TODO: ADD float16 conv
                                memcpy ( slider+space_idx, &x, x_size );
                            } else {
                                int x = atoi( slider+space_idx );
                                x_size = ( x > 127 ) + 1;
                                memcpy( slider+space_idx, &x, x_size );
                            }

                            

                            // move idx back
                            // write over the base point
                            // probably write on an output buffer
                            // Then write the output buffer into a file
                        }
                    }
            }
            fwrite(slider, 1, idx+1, outputFP);
            idx = 0;
        }
    }
}
