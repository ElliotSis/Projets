#include <stdio.h>
#include <stdlib.h>

float xMinNormaliseSimple(){
	float z = 1.;
	int n = 0;
	while(z/2 > 0 && n < 126){
		z/=2;
		n++;
	}
	return z;
}

double xMinNormaliseDouble(){
	double z = 1.;
	int n = 0;
	while(z/2 > 0 && n < 1022){
		z/=2;
		n++;
	}
	return z;
}

float xMinDenormaliseSimple(){
	float z = 1.;
	while(z/2 > 0){
		z/=2;
	}
	return z;
}

double xMinDenormaliseDouble(){
	double z = 1.;
	while(z/2 > 0){
		z/=2;
	}
	return z;
}

int main(int argc, char* argv[]){
	float xMin1 = xMinNormaliseSimple();
	double xMin2 = xMinNormaliseDouble();
	float xMin3 = xMinDenormaliseSimple();
	double xMin4 = xMinDenormaliseDouble();
	printf("X min normalise (simple precision) : %g\n", xMin1);
	printf("X min normalise (double precision) : %g\n", xMin2);
	printf("X min denormalise (simple precision) : %g\n", xMin3);
	printf("X min denormalise (double precision) : %g\n", xMin4);
	return EXIT_SUCCESS;
}