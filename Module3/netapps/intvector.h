#ifndef __INTVECTOR_H__
#define __INTVECTOR_H__

#include <malloc.h>
#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0
#define INT_MIN -2147483648
#define INT_MAX 2147483647

//Store and track the stored data
typedef struct sVector
{
    int *items;
    int capacity;
    int size;
} intvector;

int vectorSize(intvector *v);

int vectorResize(intvector *v, int capacity);

int vectorPushBack(intvector *v, int item);

int vectorSet(intvector *v, int index, int item);

int vectorGet(intvector *v, int index);

int vectorDelete(intvector *v, int index);

int vectorFree(intvector *v);

void vector_init(intvector *v);

#endif