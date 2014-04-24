#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int i,j;
	int sizeA=atoi(argv[1]);//szerokość macierzy
	int sizeB=atoi(argv[2]);//wysokość macierzy
	int* A = (int*)malloc(sizeA*sizeB*sizeof(int*));	
	srand(1);
	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeB;j++){
			A[i*sizeA+j]=rand()%10;
		}
	}
	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeB;j++){
			printf("%d ",A[i*sizeA+j]);
		}
	}
	return 0;
	free(A);
}
