#include <stdio.h>
#include <malloc.h>
#include "player.h"

static void move_up(struct player *p){
    p->position.y -= STEP_LENGTH_OY;
}

static void move_down(struct player *p){
    p->position.y += STEP_LENGTH_OY;
}

static void move_left(struct player *p){
    p->position.x -= STEP_LENGTH_OX;
}

static void move_right(struct player *p){
    p->position.x += STEP_LENGTH_OX;
}

struct player* init_player(int number, int id){
    struct player *p = (struct player *)malloc(sizeof(struct player));
    if (!p){
        fprintf(stderr, "%s, line %d, file %s\n", EMALLOC_MSG, __LINE__, __FILE__);
        return NULL;
    }
    int type = number % COUNT_OF_DIRECTIONS;

    switch(type){
        case 0:
            p->move = move_up;
            p->direction = UP;
            break;
        case 1:
            p->move = move_down;
            p->direction = DOWN;
            break;
        case 2: 
            p->move = move_left;
            p->direction = LEFT;
            break;
        case 3:
            p->move = move_right;
            p->direction = RIGHT;
            break;
        default:
            break;
    }
    p->count_lifes = 1;
    p->info.id = id;
    return p;
}

void set_player_position(struct player *p, struct point coords){
    p->position.x = coords.x;
    p->position.y = coords.y;
}

int is_player_alive(struct player *p){
    return p->count_lifes > 0 ? 1 : 0;
}

void kill_player(struct player *p){
    p->count_lifes = 0;
    printf("Player #%d was killed\n", p->info.id);
}

void destroy_player(struct player *p){
    free(p);
    p = NULL;
}

void player_log(struct player *p, const char *msg){
    fprintf(stdout, "Player %d: %s\n", p->info.id, msg);
}
