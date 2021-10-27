// variant 6

/*
* Стек моделируется при помощи динамического массива указателей на линейные 
* массивы размерности N целых. Указатель стека – два индекса – в массиве 
* указателей и линейном массиве. В операции push при переполнении текущего 
* линейного массива в массив указателей добавляется новый, если операция pop 
* переходит к предыдущему массиву, то текущий утилизуется.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>


#define MAXCHUNKSIZE 100

typedef struct Stack {
    // указатели на вершину стека
    int rowhead, colhead;
    // размер линейных массивов, используемых для хранения элементов
    int chunksize; 
    int **items;
} stack;

stack *init(int);
int pop(stack *);
void push(stack *, int );
void destroy(stack *);

void getStackInfo(stack *);

/***************** M A I N *****************/
int main(int argc, char *argv[]){
    stack *s = init(10);
    getStackInfo(s);

    for(int i = 1; i <= 20; ++i){
        push(s, i);
        getStackInfo(s);
    }

    for(int i = 1; i <= 21; ++i){
        printf("Pop: %d\n", pop(s));
        getStackInfo(s);
    }
    destroy(s);
    return EXIT_SUCCESS;
}
/*******************************************/

stack *init(int chunksize){
    if (chunksize < 0 || chunksize > MAXCHUNKSIZE)
        return NULL;
    stack *s = (stack*)malloc(sizeof(stack));
    s->chunksize = chunksize;
    s->items = (int**)malloc(sizeof(int*));
    if (s->items == NULL)
        return NULL;
    
    s->items[0] = (int*)malloc(s->chunksize * sizeof(int));
    if (s->items[0] == NULL)
        return NULL;
    s->rowhead = 0;
    s->colhead = -1;
    return s;
}

int pop(stack *s){
    int value;
    if (s->colhead < 0){
        fprintf(stderr, "Queue is empty\n");
        return INT_MIN;
    }
    else if(s->colhead == 0 && s->rowhead > 0){    
        value = s->items[s->rowhead][s->colhead];
        free(s->items[s->rowhead]);   
        s->colhead = s->chunksize - 1;
        int **items = realloc(s->items, sizeof(int *) * s->rowhead);
        if (items){
            s->items = items;
            (s->rowhead)--;
            return value;
        }
        else{
            perror("realloc");
            return INT_MIN;
        }
    }
    else{
        return (s->items[s->rowhead][s->colhead--]);
    }
} 

void push(stack *s, int elem){
    if(s->colhead == s->chunksize - 1){
        int **items = realloc(s->items, sizeof(int *) * (s->rowhead + 2));
        if (items){
            s->items = items;
            s->rowhead++;
            s->colhead = 0;
            s->items[s->rowhead] = (int*)malloc(sizeof(int) * s->chunksize);
            s->items[s->rowhead][s->colhead] = elem;
        }
        else {
            perror("realloc");
            return;
        } 
    }
    else{
        s->items[s->rowhead][++s->colhead] = elem;
    }
}

void destroy(stack *s){
    for(int i = 0; i <= s->rowhead; ++i){
        free(s->items[i]);
        s->items[i] = NULL;
    }
    free(s->items);
    s->items = NULL;
}

void getStackInfo(stack *s){
    printf("\n--------------- Stack info ---------------\n");
    printf("Chunk size: %d\n", s->chunksize);
    printf("Head elem: [%d][%d]\n", s->rowhead, s->colhead);
    printf("\n");
}
