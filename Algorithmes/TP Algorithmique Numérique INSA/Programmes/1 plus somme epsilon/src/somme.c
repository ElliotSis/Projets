#include <stdio.h>
#include <stdlib.h>

double calculY(){
	double y = 1.;
	int i;
	for(i = 0; i < 55 ; i++){
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
	float sum2S = sommeEpsilonSimple(2) + 1;
	float sum10S = sommeEpsilonSimple(10) + 1;
	float sum100S = sommeEpsilonSimple(100) + 1;
	float sum1000S = sommeEpsilonSimple(1000) + 1;
	double sum2D = sommeEpsilonDouble(2) + 1;
	double sum10D = sommeEpsilonDouble(10) + 1;
	double sum100D = sommeEpsilonDouble(100) + 1;
	double sum1000D = sommeEpsilonDouble(1000) + 1;
	printf("Somme pour n = 2 (simple precision) : %.50f\n", sum2S);
	printf("Somme pour n = 2 (double precision) : %.50f\n", sum2D);
	printf("Somme pour n = 10 (simple precision) : %.50f\n", sum10S);
	printf("Somme pour n = 10 (double precision) : %.50f\n", sum10D);
	printf("Somme pour n = 100 (simple precision) : %.50f\n", sum100S);
	printf("Somme pour n = 100 (double precision) : %.50f\n", sum100D);
	printf("Somme pour n = 1000 (simple precision) : %.50f\n", sum1000S);
	printf("Somme pour n = 1000 (double precision) : %.50f\n", sum1000D);
	return EXIT_SUCCESS;
}