#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int instances;

int generate_num(int min, int max){
    srand(time(0) * instances++);
    return (rand() % (max - min + 1)) + min;
}

void help() {
    printf("");
}

void generate_list(FILE* fp){
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);
    
    char buff[len];
    int newlines[255];
    int i = 0, newline_count;
    
    for (; !feof(fp); i++){

    }
}

void generate_word(){
    char buff[100];
    for(; !feof(fp); i++ ){
        buff[i] = fgetc(fp);
        if (buff[i] == '\n') {
            if (generate_num(1, 4) == 2) break;
            last_newline = i+1;
        }
    }

    buff[i] = 0;
    printf("Your Word is: %s\n", buff + last_newline);
}

int main(int argc, char** argv){
    if (argc < 2) return -1;
    
    // check for help or list command
    FILE* fp = fopen(argv[1], "r");

    
    // buff[len] = 0; 
    // printf("%s\n", buff);
    return 0;
}
