#include <stdio.h>
#include <stdlib.h>

double calculY(){
	double y = 1.;
	int i;
	for(i = 0; i < 24 ; i++){
		y/=2;
	}
	return y;
}

float sommeEpsilonSimple(int n){
	float y = calculY(), z = y;
	int i;
	for (i = 1 ; i < n ; i++){
		z+=y;
	}
	return z;
}

double sommeEpsilonDouble(int n){
	double y = calculY(), z = y;
	int i;
	for (i = 1 ; i < n ; i++){
		z+=y;
	}
	return z;
}

int main(int argc, char* argv[]){
	float sumS = sommeEpsilonSimple(100000000);
	double sumD = sommeEpsilonDouble(100000000);
	printf("Somme pour n = 100000000 (simple precision) : %.50f\n", sumS);
	printf("Somme pour n = 100000000 (double precision) : %.50f\n", sumD);
	return EXIT_SUCCESS;
}