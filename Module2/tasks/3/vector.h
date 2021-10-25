#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <malloc.h>
#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0

//Store and track the stored data
typedef struct sVector
{
    void **items;
    int capacity;
    int size;
} vector;

int vectorSize(vector *v);

int vectorResize(vector *v, int capacity);

int vectorPushBack(vector *v, void *item);

int vectorSet(vector *v, int index, void *item);

void *vectorGet(vector *v, int index);

int vectorDelete(vector *v, int index);

int vectorFree(vector *v);

int vectorSort(vector *v, size_t size, int (*compar)(const void *, const void *));

#endif