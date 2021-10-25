// variant 5

#include "task1.h"


int main(int argc, char *argv[]){

    sdata *data = (sdata*)malloc(sizeof(sdata));
    readData(data);
    printData(data);
    return EXIT_SUCCESS;
}

void readData(sdata *data){
    char buf[10];
    int size;
    char newline;

    printf("Count of items:\n");
    fgets(buf, 10, stdin);
    sscanf(buf, "%d", &size);
    data->size = size;
    data->items = (sitem*)malloc(size*sizeof(sitem));

    printf("Enter type and value:\n");

    for(int i = 0; i < size; ++i){
        printf("[%d]: ", i);
        scanf("%c %ld", &(data->items[i].type), &(data->items[i].value));
        scanf("%c", &newline); // eat trailing newline
    }
}

void printData(sdata *data){
    printf("\nSize: %d\n", data->size);
    printf("#\t\tType\t\tValue\n");
    for(int i = 0; i < data->size; ++i){
        switch(data->items[i].type){
            case '0':{
                printf("%d\t\t%c (char)\t%c\n", i, data->items[i].type, (char)data->items[i].value);
                break;
            }
            case '1':{
                printf("%d\t\t%c (int)\t\t%d\n", i, data->items[i].type, (int)data->items[i].value);
                break;
            }
            case '2':{
                printf("%d\t\t%c (long)\t%ld\n", i, data->items[i].type, data->items[i].value);
                break;
            }
            default:
                printf("Unknown type\n");
        }
        
    }
}