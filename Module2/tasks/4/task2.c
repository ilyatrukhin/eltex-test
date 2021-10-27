// variant 7
/*
* Очередь моделируется при помощи динамического массива указателей 
* на линейные массивы размерности N целых. Указатели на первый и последний  
* элементы очереди – два индекса – в массиве указателей и линейном массиве. 
* В операции добавления при переполнении текущего линейного массива в массив 
* указателей добавляется новый, в операции извлечения – при переходе к 
* следующему линейному массиву текущий утилизуется (указатели в массиве 
* указателей смещаются к началу).
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define MAXCHUNKSIZE 100

typedef struct Queue {
    // указатели на первый и последний элементы в очереди
    int rowfirst, colfirst, rowlast, collast;
    // размер линейных массивов, используемых для хранения элементов
    int chunksize; 
    int **items;
} queue;

queue *init(int);
int pop(queue *);
void push(queue *, int );
void destroy(queue *);

void getQueueInfo(queue *);

/***************** M A I N *****************/
int main(int argc, char *argv[]){
    queue *q = init(5);
    getQueueInfo(q);

    for(int i = 1; i <= 20; ++i){
        push(q, i);
        getQueueInfo(q);
    }

    for(int i = 0; i <= 25; ++i){
        printf("Pop: %d\n", pop(q));
        getQueueInfo(q);
    }
    
    destroy(q);
    return EXIT_SUCCESS;
}
/*******************************************/

queue *init(int chunksize){
    if (chunksize < 0 || chunksize > MAXCHUNKSIZE)
        return NULL;
    queue *q = (queue*)malloc(sizeof(queue));
    q->chunksize = chunksize;
    q->items = (int**)malloc(sizeof(int*));
    if (q->items == NULL)
        return NULL;
    
    q->items[0] = (int*)malloc(q->chunksize * sizeof(int));
    if (q->items[0] == NULL)
        return NULL;
    q->rowfirst = 0;
    q->colfirst = 0;
    q->rowlast = 0;
    q->collast = -1;

    return q;
}

int pop(queue *q){
    int value;
    if (q->rowfirst == q->rowlast && q->colfirst > q->collast){
        fprintf(stderr, "Queue is empty\n");
        return INT_MIN;
    }
    else if(q->colfirst == q->chunksize - 1){
        if(q->rowlast > 0){
            value = q->items[q->rowfirst][q->colfirst];
            free(q->items[q->rowfirst]);
            for(int i = q->rowfirst; i < q->rowlast; ++i){
                q->items[i] = q->items[i+1];
            }
            q->colfirst = 0;
            int **items = realloc(q->items, sizeof(int *) * (q->rowlast - q->rowfirst));
            if (items){
                q->items = items;
                (q->rowlast)--;
                return value;
            }
            else{
                perror("realloc");
                return INT_MIN;
            }
        }
        else if (q->rowlast == 0 && q->collast == q->chunksize - 1){
            value = q->items[q->rowlast][q->collast];
            q->rowfirst = 0;
            q->colfirst = 0;
            q->rowlast = 0;
            q->collast = -1;
            return value; 
        }      
        else 
            return INT_MIN;
    }
    else{
        if(q->colfirst <=  q->collast || (q->colfirst > q->collast && q->rowfirst < q->rowlast)){
            return (q->items[q->rowfirst][q->colfirst++]);
        }
        else
            return INT_MIN;
    }
} 

void push(queue *q, int elem){
    if(q->collast == q->chunksize - 1){
        int **items = realloc(q->items, sizeof(int *) * (q->rowlast - q->rowfirst + 2));
        if (items){
            q->items = items;
            q->rowlast++;
            q->collast = 0;
            q->items[q->rowlast] = (int*)malloc(sizeof(int) * q->chunksize);
            q->items[q->rowlast][q->collast] = elem;
        }
        else {
            perror("realloc");
            return;
        } 
    }
    else{
        q->items[q->rowlast][++q->collast] = elem;
    }
}

void destroy(queue *q){
    for(int i = q->rowfirst; i <= q->rowlast; ++i){
        free(q->items[i]);
        q->items[i] = NULL;
    }
    free(q->items);
    q->items = NULL;
}

void getQueueInfo(queue *q){
    printf("\n--------------- Queue info ---------------\n");
    printf("Chunk size: %d\n", q->chunksize);
    printf("First elem: [%d][%d]\n", q->rowfirst, q->colfirst);
    printf("Last elem: [%d][%d]\n", q->rowlast, q->collast);
    printf("\n");
}
