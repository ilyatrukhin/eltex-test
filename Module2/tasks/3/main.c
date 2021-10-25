#include <stdio.h>
#include "vector.h"

void vector_init(vector *v)
{
    //initialize the capacity and allocate the memory
    v->capacity = VECTOR_INIT_CAPACITY;
    v->size = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

typedef struct student{
    int age;
} student;

int main(int argc, char *argv[])
{
    vector students;
    student *st1, *st2;

    st1 = (student*)malloc(sizeof(student));
    st2 = (student*)malloc(sizeof(student));
    st1->age = 19;
    st2->age = 23;


    int i =0;
    //init vector
    vector_init(&students);

    //Add data in vector
    vectorPushBack(&students, (student*)st1);
    vectorPushBack(&students, (student*)st2);
  
    for (i = 0; i < vectorSize(&students); i++)
    {
        printf("%d\n", ((student*)vectorGet(&students, i))->age);
    }
    //Set the data at index 0
    //v.set(&v,0,"9.0001");
    //printf("\n\n\nVector list after changes\n\n\n");
    //print the data and type cast it
    //for (i = 0; i < v.size(&v); i++)
    //{
    //    printf("%lf", (double)v.get(&v, i));
    //}
    free(st1);
    free(st2);
    return 0;
}