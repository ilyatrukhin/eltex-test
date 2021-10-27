// variant 1
/*
* Функция получает линейный массив целых, находит в нем последовательности 
* подряд возрастающих значений и возвращает их в динамическом массиве указателей 
* на линейные массивы (аналог двумерного массива). В каждом из линейных 
* динамических массивов содержится копия возрастающей последовательности, начиная 
* с индекса 1, а под индексом 0 содержится его длина. Невозрастающие значения 
* включаются в отдельный массив, добавляемый в конец (или начало) массива указателей.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Table{
    int **ptrs;
    int count;
} table;

size_t getStartSeq(int *, size_t , size_t );
size_t getEndSeq(int *, size_t , size_t );
void appendArray(table *, int *, size_t );
void extractArray(int *, size_t , size_t , size_t );
table *initTable();
void destroy(table *);
void printTable(table *);

/***************** M A I N *****************/
int main(int argc, char *argv[]){
    table *t = initTable();
    size_t n;
    int *arr;
    char newline;
    int curlen;
    int shift;

    size_t start = 0, end;

    printf("Введите размер массива: ");
    scanf("%ld", &n);
    scanf("%c", &newline);
    arr = (int*)malloc(n * sizeof(int));
    for(size_t i = 0; i < n; ++i){
        printf("[%ld]:", i);
        scanf("%d", &arr[i]);
        scanf("%c", &newline);
    }

    end = n - 1;
    curlen = n;

    start = getStartSeq(arr, start, curlen);
    end = getEndSeq(arr, start, curlen);
    while(start < curlen - 1){  
        shift = end - start + 1;
        appendArray(t, arr + start, shift);
        extractArray(arr, curlen, start, end);
        curlen -= shift;  
        start = getStartSeq(arr, end - shift + 1, curlen);
        end = getEndSeq(arr, start, curlen);
    }

    appendArray(t, arr, curlen);
    
    
    printf("\n\n");
    printTable(t);
    
    destroy(t);
    free(arr);
    arr = NULL;
    return EXIT_SUCCESS;
}
/*******************************************/

table *initTable(){
    table *t = (table*)malloc(sizeof(table));
    t->ptrs = NULL;
    t->count = 0;
    return t;
}

void destroy(table *t){
    for(size_t i = 0; i < t->count; ++i){
        free(t->ptrs[i]);
        t->ptrs[i] = NULL;
    }
    free(t);
    t = NULL;
}

size_t getStartSeq(int *items, size_t start, size_t len){
    for(size_t i = start; i < len - 1; ++i){
        if(items[i] < items[i+1])
            return i;
    }
    return len - 1;
}

size_t getEndSeq(int *items, size_t start, size_t len){
    for(size_t i = start + 1; i < len - 1; ++i){
        if(items[i] >= items[i+1])
            return i;
    }
    return len - 1; 
}

void appendArray(table *t, int *arr, size_t len){
    int **ptrs = realloc(t->ptrs, (++t->count) * sizeof(int*));
    if(ptrs){
        t->ptrs = ptrs;
        t->ptrs[t->count-1] = (int*)malloc((len+1) * sizeof(int));
        t->ptrs[t->count-1][0] = len;
        for(size_t i = 0; i < len; i++){
            t->ptrs[t->count-1][i + 1] = arr[i];
        }
    }
    else
        perror("realloc");
}

void extractArray( int *arr, size_t len, size_t start, size_t end) {
	size_t shift = end - start + 1;
	for(int i = start; i < start + len - end; i++){
		arr[i] = arr[i + shift];
	}
}


void printTable(table *t){
    for(size_t i = 0; i < t->count; ++i){
        printf("[%ld]: ", i);
        for(size_t j = 1; j < t->ptrs[i][0] + 1; ++j)
            printf("%d ", t->ptrs[i][j]);
        printf("\n");
    }
}