#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "multipliers.h"



long getLargePrime(int );

long getAntiderivativeRoot(long , int );


int main(int argc, char *argv[]){
	int a, b;
	double ma, mb;
	// предварительный этап
	long p = getLargePrime(1000);
	printf("p = %ld\n", p);
	multipliers *m = (multipliers*)malloc(sizeof(multipliers));
	
	getMults(m, p-1);
	printMults(m);
	
	long r = getAntiderivativeRoot(p, m->mults[0]);
	printf("r = %ld\n", r);
	
	// рабочий этап
	a = rand() % (p-2) + 1;
	ma = pow((double)m, (double)a);
	printf("a = %d\n", a);
	printf("a = %d\n", (int)ma);
	
	b = rand() % (p-2) + 1;
	mb = pow((double)m, (double)a);
	printf("a = %d\n", b);
	printf("a = %d\n", (int)mb);
	
	delMults(m);
	free(m);
	return EXIT_SUCCESS;
}



long getLargePrime(int value){
	if(value < 3) 
		return 1;
	int n; 
	srand(getpid());
	n = rand() % value;
	int flag;
	for(int i = n; i >= 3; --i){
		flag = 1;
		for(int j = (int)sqrt((double)i)+1; j >= 2; --j){
			if(!(i % j)){
				flag = 0;
				break;
			}
		}
		if(flag)
			return i;
	}	
	return 1;
}

long getAntiderivativeRoot(long p, int p1){

	return p + p1;
}
