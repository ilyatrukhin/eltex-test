#include <stdio.h>
#include "vector.h"

void vector_init(vector *v)
{
    //init function pointers
    v->size = vectorSize;
    v->resize = vectorResize;
    v->add = vectorPushBack;
    v->set = vectorSet;
    v->get = vectorGet;
    v->free = vectorFree;
    v->del = vectorDelete;
    //initialize the capacity and allocate the memory
    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.size = 0;
    v->vectorList.items = malloc(sizeof(void *) * v->vectorList.capacity);
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
    students.add(&students, (student*)st1);
    students.add(&students, (student*)st2);
  
    for (i = 0; i < students.size(&students); i++)
    {
        printf("%d\n", ((student*)students.get(&students, i))->age);
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