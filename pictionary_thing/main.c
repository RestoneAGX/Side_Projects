#include<stdio.h>
#include<math.h>
#include<rand.h>

int generate_num(int min, int max){
    srand(time(0));
    return (rand() % (max - min + 1)) + min;
}

void help() {
    printf("");
}

void (*ftable[])() = {};

int main(int argc, char** argv){
    if (argc < 2) return -1;
    // check for help or list command

    
    FILE* fp = fopen(argv[1], "r");
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    char buff[len];
    int last_newline = 0;
    unsigned char newline_count = 0;
    unsigned char target_count = generate_num(1, len);
    char c;

    for(int i = 0; !feof(fp); i++ ){
        c = fgetc(fp);
        if (c == '\n') {
            last_newline = i;
            if (generate_num == 1){
                fwrite
            }
        }
    }
    // randomly select one


    return 0;
}
