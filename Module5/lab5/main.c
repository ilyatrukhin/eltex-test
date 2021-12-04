#include<stdio.h>
int main(int argc, char **argv){
	extern float f1(float);
	extern float f2(float);
	printf("f1(4,0): %f\n", f1(4.0));
	printf("f2(4,0): %f\n", f2(4.0));

	return 0;
}