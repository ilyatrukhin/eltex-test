#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main(int argc, char *argv[]){
	const int a = 10;
	const int b = 4;
	printf("Sum: %d\n", sum(a, b));
	printf("Sub: %d\n", sub(a, b));
	printf("Mult %d\n", mult(a, b));
	return 0;
}
