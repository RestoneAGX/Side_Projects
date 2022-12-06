#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int arg_count;
char** args;

FILE *fp;

void List() {
    printf("\nStarting...\n");
    while ( !feof(fp) )
        printf("%c", (char) fgetc(fp));
}

void Add() {
    char * output = strcat(args[2],"␇\n");
    fwrite(output, 1, strlen(output), fp);
}

void Remove() {
    char * output;
    unsigned char hit = 0;
    int len = strlen(args[2]);
    int i = 0, x = len+1;

    for ( ; !feof(fp); ++i ) {
       
        char c = fgetc(fp);

        if ( c == args[2][hit] ) hit++;
        else hit = 0;

        printf("%d\n", i);

        if ( hit == len && x > 0)
            output[ i-- - x-- ] = c;
        else{
            output = realloc(output, i);
            strncat(output, &c, 1);
        }

        // printf("%c", c);
    }
    
    printf("\n\n%s", output);

    remove("test.txt");
    fp = fopen("test.txt", "w");
    fwrite(output, 1, i, fp);
    free(output);
}

void Help(){ 
    printf("I'm helping\n"); 
}

// NOTE: Without the parameter brackets, it's apparently not either a function pointer or a pointer, interesting
void (*funcs[4])() = { Help, List, Add, Remove };

char perm_opts[2][2] = { "r+", "a+" };

int main(int argc, char ** argv){
    
    arg_count = argc;
    args = argv;

    int ix = (argc > 1);
    int point = (argv[ix][0] == 'l') + 
              ( (argv[ix][0] == 'a' && argc > 2 ) * 2 ) +
              ( (argv[ix][0] == 'r' ) * 3 );
    
    fp = fopen("test.txt", perm_opts[(point == 2)]); 
    
    (*funcs[point])();
    
    printf("ix: %d, cmd: %d\n", ix, point);

    // float starting = (float) clock()/CLOCKS_PER_SEC;
    // printf("%f\n", ( (float) clock()/CLOCKS_PER_SEC ) - starting);
    
    return 0;
}

