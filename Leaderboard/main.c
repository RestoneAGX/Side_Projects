#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int arg_count;
char** args;
FILE *fp;

void List() {
    while ( !feof(fp) )
        printf("%c", (char) fgetc(fp));
}

void Add() {
    char * output = strcat(args[2],"\n");
    fwrite(output, 1, strlen(output), fp);
}

void Remove() {
    fseek(fp, 0L, SEEK_END);
    char output[ftell(fp)];
    rewind(fp);

    args[2] = strcat(args[2], "\n");
    int len = strlen(args[2]);
    unsigned char hit = 0;
    int i = 0;

    for ( ; !feof(fp); ++i ) {
       
        char c = fgetc(fp);
        
        unsigned char cond = (c == args[2][hit]);
        hit = (hit + cond) * cond;

        unsigned char len_temp = (hit == len);
        i -= hit * len_temp;
        hit *= !len_temp;

        output[i] = c;
    }
    
    remove("test.txt");
    fp = fopen("test.txt", "w+");
    fwrite(output, 1, i-1, fp);
}

void Help(){ 
    printf(" list -> list leaderboards,\n add -> add [target],\n remove -> remove [target]\n | use \" \" for words with spaces |\n"); 
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
              ( (argv[ix][0] == 'r' && argc > 2 ) * 3 );
    
    fp = fopen("test.txt", perm_opts[(point == 2)]); 
    
    (*funcs[point])();
    
    // float starting = (float) clock()/CLOCKS_PER_SEC;
    // printf("%f\n", ( (float) clock()/CLOCKS_PER_SEC ) - starting);
    
    return 0;
}

