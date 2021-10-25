// variant 3

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct sData{
    int size;
    int *items;
} sdata;

void readData(sdata *);
void printData(sdata *);

void printUniqSeq(sdata *, int, int);
void printRepSeq(int, int);

int getStartRep(int *, int, int);
int getEndRep(int *, int, int);


/************** M A I N *************/

int main(int argc, char *argv[]){
    sdata *data = (sdata*)malloc(sizeof(sdata));
    readData(data);
    printData(data);
    printf("\n");
    free(data);
    return EXIT_SUCCESS;
}
/************************************/

void readData(sdata *data){
    char buf[10];
    int size;
    char newline;

    printf("Count of items:\n");
    fgets(buf, 10, stdin);
    sscanf(buf, "%d", &size);
    data->size = size;
    data->items = (int*)malloc(size*sizeof(int));

    printf("Enter value:\n");

    for(int i = 0; i < size; ++i){
        printf("[%d]: ", i);
        scanf("%d", &(data->items[i]));
        scanf("%c", &newline); // eat trailing newline
    }
}

void printData(sdata *data){
    int start = 0;
    int startRep, endRep;
    printf("\nSize: %d\n", data->size);
    
    while(start < data->size){       
        startRep = getStartRep(data->items, start, data->size);
        // есть подпоследовательность из одинаковых чисел
        if (startRep != data->size){
            endRep = getEndRep(data->items, startRep + 1, data->size);
        }
        else
            endRep = data->size;

        if(start < startRep)
            printUniqSeq(data, start, startRep);
        if(startRep < endRep)
            printRepSeq(data->items[startRep], endRep - startRep + 1);

        start = endRep + 1;
    }
}

void printUniqSeq(sdata *data, int start, int end){
    int count = end - start;
    printf("(%d) ", count);
    for(int i = start; i < end; i++){
        printf("%d ", data->items[i]);
    }
}

void printRepSeq(int number, int count){
    printf("(-%d) %d ", count, number);
}

// поиск начала последовательности одинаковых чисел
int getStartRep(int *items, int start, int len){
    for(int i = start; i < len - 1; i++){
        if (items[i] == items[i+1]){
            return i;
        }
    }
    return len;
}

// поиск конца последовательности одинаковых чисел
int getEndRep(int *items, int start, int len){
    for(int i = start; i < len - 1; i++){
        if (items[i] != items[i+1]){
            return i;
        }
    }
    return len - 1;
}