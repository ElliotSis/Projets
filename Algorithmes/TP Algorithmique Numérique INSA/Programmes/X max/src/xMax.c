#include <stdio.h>
#include <stdlib.h>

float xMaxNormaliseSimple(){
	float z = 1., inf = 1./0., x;
	while(2*z < inf){
		z*=2;
	} // Plus grand exposant
	x = z/2;
	while(z + x < inf){
		z+=x;
		x/=2;
	} // Plus grande mantisse
	return z;
}

double xMaxNormaliseDouble(){
	double z = 1., inf = 1./0., x;
	while(2*z < inf){
		z*=2;
	} // Plus grand exposant
	x = z/2;
	while(z + x < inf){
		z+=x;
		x/=2;
	} // Plus grande mantisse
	return z;
}

float xMaxDenormaliseSimple(){
	float xMinNorm = 1., xMinDenorm = 1.;
	int n = 0;
	while(xMinDenorm/2 > 0){
		xMinDenorm/=2;
	}
	while(xMinNorm/2 > 0 && n < 126){
		xMinNorm/=2;
		n++;
	}
	return (xMinNorm - xMinDenorm);
}

double xMaxDenormaliseDouble(){
	double xMinNorm = 1., xMinDenorm = 1.;
	int n = 0;
	while(xMinDenorm/2 > 0){
		xMinDenorm/=2;
	}
	while(xMinNorm/2 > 0 && n < 1022){
		xMinNorm/=2;
		n++;
	}
	return (xMinNorm - xMinDenorm);
}

int main(int argc, char* argv[]){
	float xMax1 = xMaxNormaliseSimple();
	double xMax2 = xMaxNormaliseDouble();
	float xMax3 = xMaxDenormaliseSimple();
	double xMax4 = xMaxDenormaliseDouble();
	printf("X Max normalise (simple precision) : %g\n", xMax1);
	printf("X Max normalise (double precision) : %g\n", xMax2);
	printf("X Max denormalise (simple precision) : %g\n", xMax3);
	printf("X Max denormalise (double precision) : %g\n", xMax4);
	return EXIT_SUCCESS;
}