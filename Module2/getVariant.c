#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr, "Usage: %s <symbol> <count of variants>\n", argv[0]);
        return 1;
    }
    int count = atoi(argv[2]);
    printf("ASCII code: %d, variant: %d\n", (int)argv[1][0], (int)argv[1][0] % count + 1);
    return 0;
} 