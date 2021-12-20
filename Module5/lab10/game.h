#ifndef __GAME_H__
#define __GAME_H__

#include "player.h"
#include "table.h"

void take_cell(struct table *, struct player *);
void free_cell(struct table *, struct player *);
int player_prestep(struct player *, int);

void make_step(struct table *, struct player *);
void start_game();
void finish_game();

#endif