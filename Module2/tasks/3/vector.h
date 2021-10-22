#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <malloc.h>

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0

//Store and track the stored data
typedef struct sVectorList
{
    void **items;
    int capacity;
    int size;
} sVectorList;

//structure contain the function pointer
typedef struct sVector vector;
struct sVector
{
    sVectorList vectorList;
    //function pointers
    int (*size)(vector *);
    int (*resize)(vector *, int);
    int (*add)(vector *, void *);
    int (*set)(vector *, int, void *);
    void *(*get)(vector *, int);
    int (*del)(vector *, int);
    int (*free)(vector *);
};

int vectorSize(vector *v);

int vectorResize(vector *v, int capacity);

int vectorPushBack(vector *v, void *item);

int vectorSet(vector *v, int index, void *item);

void *vectorGet(vector *v, int index);

int vectorDelete(vector *v, int index);

int vectorFree(vector *v);

#endif