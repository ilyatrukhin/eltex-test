#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "game.h"


void battle(struct player *p1, struct player *p2){
    printf("Battle between player %d (lifes: %d) and player %d (lifes: %d)\n", p1->info.id, p1->count_lifes, p2->info.id, p2->count_lifes);
    if(p1->count_lifes > p2->count_lifes) {
        kill_player(p2);
    }
    else if(p1->count_lifes < p2->count_lifes){
        kill_player(p1);
    }
    else {
        if (p1->info.id > p2->info.id){
            kill_player(p2);
        }
        else {
            kill_player(p1);
        }
    }

}

void take_cell(struct table *tbl, struct player *p){
    tbl->cells[p->position.x * tbl->size + p->position.y]->player_ptr = p;
    p->count_lifes += tbl->cells[p->position.x * tbl->size + p->position.y]->weight;
}

void free_cell(struct table *tbl, struct player *p){
    tbl->cells[p->position.x * tbl->size + p->position.y]->player_ptr = NULL;
}

int player_prestep(struct player *p, int size){
    switch(p->direction){
        case UP:
            if(p->position.y == 0)
                return OUT_OF_RANGE;
        case DOWN:
            if(p->position.y == size - 1)
                return OUT_OF_RANGE;
        case LEFT:
            if(p->position.x == 0)
                return OUT_OF_RANGE;
        case RIGHT:
            if(p->position.x == size - 1)
                return OUT_OF_RANGE;
    }
    return 0;
}

void make_step(struct table *tbl, struct player *p){
    char msg[40];
    if(player_prestep(p, tbl->size) != OUT_OF_RANGE){
        free_cell(tbl, p);
        
        sprintf(msg, "current position - (%d, %d)", p->position.x, p->position.y);
        player_log(p, msg);
        
        p->move(p);
        
        sprintf(msg, "new position - (%d, %d)", p->position.x, p->position.y);
        player_log(p, msg);
        
        struct player *p2 = (struct player*)is_cell_busy(tbl, (struct point){p->position.x, p->position.y});
        if(p2){
            battle(p, p2);
        }
        if(p->count_lifes){
            take_cell(tbl, p);
        }
    }
    else{
        kill_player(p);
        free_cell(tbl, p);
    }
}

