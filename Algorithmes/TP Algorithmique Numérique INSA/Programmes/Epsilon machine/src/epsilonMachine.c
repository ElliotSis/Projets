#include <stdio.h>
#include <stdlib.h>

float epsilonMachineSimple(){
	float z = 1.;
	while(1 + z/2 > 1){
		z/=2;
	}
	return z;
}

double epsilonMachineDouble(){
	double z = 1.;
	while(1 + z/2 > 1){
		z/=2;
	}
	return z;
}

int main(int argc, char* argv[]){
	float eps1 = epsilonMachineSimple();
	double eps2 = epsilonMachineDouble();
	printf("Epsilon machine (simple precision) : %g\n", eps1);
	printf("Epsilon machine (double precision) : %g\n", eps2);
	return EXIT_SUCCESS;
}