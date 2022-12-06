#include <stdio.h>

FILE *fp;

void Remove() {

}

int main(){
    fp = fopen("test2.txt", "r+");

    Remove();
    return 0;
}
