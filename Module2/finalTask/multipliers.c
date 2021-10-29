#include "multipliers.h"

void getMults(multipliers *m, long number){
	int size = 2;
	m->value = number;
	m->count = 0;
	m->mults = (int*)malloc(size * sizeof(int));
	long tmp = number;
	int mult = 2;
	
	while(tmp > 1){
		while(!(tmp % mult)){
			tmp /= mult;
			if(++m->count > size){
				size *= 2;
				m->mults = realloc(m->mults, size);
			}
			m->mults[m->count - 1] = mult;
		}
		++mult;
	}
}

void printMults(multipliers *m){
	printf("Number: %ld\n", m->value);
	for(int i = 0; i < m->count; ++i){
		printf("%d ", m->mults[i]);
	}
	printf("\n");
}

void delMults(multipliers *m){
	
	free(m->mults);
}
