#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

unsigned char start = 0;
int arg_count;
char** args;

FILE *fp;

void List() {
    printf("\nStarting...\n");
    while ( !feof(fp) )
        printf("%c", (char) fgetc(fp));
}

void Add() {
     
}

void Remove() {}

void Help(){ printf("I'm helping\n"); }

// NOTE: Without the parameter brackets, it's apparently not either a function pointer or a pointer, interesting
void (*funcs[4])() = { Help, List, Add, Remove };

int main(int argc, char ** argv){
    arg_count = argc;
    args = argv;

    int ix = (argc > 1);
    int point = (argv[ix][0] == 'l') + ( (argv[ix][0] == 'a' || ) * 2 ) + ( (argv[ix][0] == 'r') * 3 );
    (*funcs[point])();
    printf("ix: %d, cmd: %d\n", ix, point);
    /*
    if (argc == 0) return -1;

    fp = fopen("test.txt", "rb");
   
    assert(fp != NULL);

    // float starting = (float) clock()/CLOCKS_PER_SEC;

    // Branchless if
    if (argv[1][0] == '-')
        start += 1;
    
   // Make this Branchless
    switch(argv[1][start]){
        case 'l': List();
            break;

        case 'a': Add(argc, argv); 
            break;

        case 'r': Remove();
            break;

        default: Help();
            break;
    }

    // printf("%f\n", ( (float) clock()/CLOCKS_PER_SEC ) - starting);
    */
    return 0;
}

