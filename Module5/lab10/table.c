#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "table.h"

/************ TABLE ************/
struct table *init_table(int size) {
    struct table *tbl = (struct table *)malloc(sizeof(struct table));
    if(!tbl){
        fprintf(stderr, "%s, line %d, file %s\n", EMALLOC_MSG, __LINE__, __FILE__);
        return NULL;
    }
    tbl->size = size;
    if((tbl->cells = (struct cell**)malloc(size*size*sizeof(struct cell*)))){
        for(int i = 0; i < size*size; ++i){
            tbl->cells[i] = (struct cell*)malloc(sizeof(struct cell));
            if(!tbl->cells[i]){
                return NULL;
            }
            tbl->cells[i]->player_ptr = NULL;
            tbl->cells[i]->weight = rand() % (MAX_CELL_WEIGHT - MIN_CELL_WEIGHT) + MIN_CELL_WEIGHT;
        }
        return tbl;
    }
    else
        return NULL;
}

void print_table(struct table *tbl){
    for(int i = 0; i < tbl->size; ++i){
        for(int j = 0; j < tbl->size; ++j){
            fprintf(stdout, "%d\t", tbl->cells[(i*tbl->size) + j]->weight);
        }
        fprintf(stdout, "\n");
    }
}

void destroy_table(struct table * tbl) {
    for(int i = 0; i < tbl->size*tbl->size; ++i){
        free(tbl->cells[i]);
    }
    free(tbl->cells);
    tbl->cells = NULL;
    free(tbl);
    tbl = NULL;
}

void* is_cell_busy(struct table *tbl, struct point coords) {
    return tbl->cells[coords.x*tbl->size + coords.y]->player_ptr;
}
