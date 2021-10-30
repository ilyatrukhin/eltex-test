/*
***********************************
****  Алгоритм Диффи-Хеллмана  ****
***********************************
* Используемые тождества:
* 1) (A * B) mod c = (A mod c * B mod c) mod c
* 2) A^n mod c = ((A mod c)^n) mod c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "multipliers.h"

long getLargePrime(int );

int getAntiderivativeRoot(multipliers * , int );

int powBigMod(int , int , int );

int main(int argc, char *argv[]){
	int a, b, keyA, keyB;
	int ma, mb;
	// предварительный этап
	long p = getLargePrime(1000);
	printf("p = %ld\n", p);
	multipliers *m = (multipliers*)malloc(sizeof(multipliers));
	
	// функция Эйлера для простого числа p равна p-1;
	// находим простые множители функции Эйлера
	getMults(m, p-1);
	//printMults(m);

	int r = getAntiderivativeRoot(m, p);
	printf("r = %d\n", r);

	// рабочий этап
	// выбирается большое секретное число a
	a = rand() % (p-2) + 1;
	// вычисление открытого значения ma
	ma = powBigMod(r, a, p);
	printf("a = %d\n", a);
	printf("ma = %d\n", ma);
	
	// выбирается большое секретное число b
	b = rand() % (p-2) + 1;
	// вычисление открытого значения mb
	mb = powBigMod(r, b, p);
	printf("b = %d\n", b);
	printf("mb = %d\n", (int)mb);
	
	keyA = powBigMod(mb, a, p);
	keyB = powBigMod(ma, b, p);

	printf("keyA: %d\n", keyA);
	printf("keyB: %d\n", keyB);

	delMults(m);
	free(m);
	return EXIT_SUCCESS;
}

// A^n mod p
int powBigMod(int A, int n, int p){
	int d = A % p;
	long alfa = 1, betta = d, t = n;
	int bettapowt = 1;
	// A^n mod p =  d^n mod p
	// d^n = alfa * betta^t;
	while(betta != 1 && t > 1){
		if(betta > p){
			betta %= p;
		}
		if(t % 2){
			// степень нечетная
			alfa *= betta;
			--t;
		}
		else{
			// степень четная
			betta *= betta;
			t /= 2;
		}
		if(alfa > p)
			alfa %= p;
	}
	if(betta != 1)
		for(int i = 0; i < t; ++i)
			bettapowt *= betta;
	return (alfa*bettapowt) % p;
}


long getLargePrime(int value){
	if(value < 3) 
		return 1;
	int n; 
	srand(getpid());
	n = rand() % value + value;
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

int getAntiderivativeRoot(multipliers *m, int p){
	int flag;
	for(int i = 2; i < 100; ++i){
		flag = 1;
		for(int k = 0; k < m->count; ++k){
			if(powBigMod(i, (int)(m->value / m->mults[k]), p) == 1){
				flag = 0;
				break;
			}
		}
		if(flag)
			return i;
	}
	return -1;
}
