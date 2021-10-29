#ifndef __MULTIPLIERS_H__
#define __MULTIPLIERS_H__

#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef struct Multipliers{
	long value;
	int count;
	int *mults;
} multipliers;

void getMults(multipliers *, long );

void printMults(multipliers *);

void delMults(multipliers *);

#endif
