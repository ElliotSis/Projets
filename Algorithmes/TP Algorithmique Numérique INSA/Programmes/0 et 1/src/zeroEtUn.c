#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	float zero1 = 0.;
	double zero2 = 0.;
	float un1 = 1.;
	double un2 = 1.;
	printf("Zero (simple precision) : %g\n", zero1);
	printf("Zero (double precision) : %g\n", zero2);
	printf("Un (simple precision) : %g\n", un1);
	printf("Un (double precision) : %g\n", un2);
	return EXIT_SUCCESS;
}