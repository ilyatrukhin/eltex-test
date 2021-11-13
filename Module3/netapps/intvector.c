#include "intvector.h"

int vectorSize(intvector *v)
{
    int size = UNDEFINE;
    if(v)
    {
        size = v->size;
    }
    return size;
}

int vectorResize(intvector *v, int capacity)
{
    int  status = UNDEFINE;
    if(v)
    {
        int *items = realloc(v->items, sizeof(int) * capacity);
        if (items)
        {
            v->items = items;
            v->capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorPushBack(intvector *v, int item)
{
    int  status = UNDEFINE;
    if(v && item > INT_MIN && item < INT_MAX)
    {
        if (v->capacity == v->size)
        {
            status = vectorResize(v, v->capacity * 2);
            if(status != UNDEFINE)
            {
                v->items[v->size++] = item;
            }
        }
        else
        {
            v->items[v->size++] = item;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorSet(intvector *v, int index, int item)
{
    int  status = UNDEFINE;
    if(v)
    {
        if ((index >= 0) && (index < v->size))
        {
            v->items[index] = item;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorGet(intvector *v, int index)
{
    int readData = INT_MIN;
    if(v)
    {
        if ((index >= 0) && (index < v->size))
        {
            readData = v->items[index];
        }
    }
    return readData;
}

int vectorDelete(intvector *v, int index)
{
    int  status = UNDEFINE;
    int i = 0;
    if(v)
    {
        if ((index < 0) || (index >= v->size))
            return status;
        v->items[index] = INT_MIN;
        for (i = index; (i < v->size - 1); ++i)
        {
            v->items[i] = v->items[i + 1];
            v->items[i + 1] = INT_MIN;
        }
        v->size--;
        if ((v->size > 0) && ((v->size) == (v->capacity / 4)))
        {
            vectorResize(v, v->capacity / 2);
        }
        status = SUCCESS;
    }
    return status;
}

int vectorFree(intvector *v)
{
    int  status = UNDEFINE;
    if(v)
    {
        free(v->items);
        v->items = NULL;
        status = SUCCESS;
    }
    return status;
}

void vector_init(intvector *v)
{
    //initialize the capacity and allocate the memory
    v->capacity = VECTOR_INIT_CAPACITY;
    v->size = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}