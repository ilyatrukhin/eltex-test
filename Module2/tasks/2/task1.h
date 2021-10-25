#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct sItem{
    long value;
    char type;
} sitem
;
typedef struct sData{
    sitem *items;
    int size;
} sdata;

void readData(sdata *);
void printData(sdata *);

