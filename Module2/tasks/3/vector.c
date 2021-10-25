#include "vector.h"

int vectorSize(vector *v)
{
    int size = UNDEFINE;
    if(v)
    {
        size = v->size;
    }
    return size;
}

int vectorResize(vector *v, int capacity)
{
    int  status = UNDEFINE;
    if(v)
    {
        void **items = realloc(v->items, sizeof(void *) * capacity);
        if (items)
        {
            v->items = items;
            v->capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

int vectorPushBack(vector *v, void *item)
{
    int  status = UNDEFINE;
    if(v)
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

int vectorSet(vector *v, int index, void *item)
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

void *vectorGet(vector *v, int index)
{
    void *readData = NULL;
    if(v)
    {
        if ((index >= 0) && (index < v->size))
        {
            readData = v->items[index];
        }
    }
    return readData;
}

int vectorDelete(vector *v, int index)
{
    int  status = UNDEFINE;
    int i = 0;
    if(v)
    {
        if ((index < 0) || (index >= v->size))
            return status;
        v->items[index] = NULL;
        for (i = index; (i < v->size - 1); ++i)
        {
            v->items[i] = v->items[i + 1];
            v->items[i + 1] = NULL;
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

int vectorFree(vector *v)
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

int vectorSort(vector *v, size_t size, int (*compar)(const void *, const void *)){
    qsort(v, v->size, size, compar);
}