#include <stdio.h>
#include <stdlib.h>
int main(){
	int i,j,sizeA,sizeB;
	scanf("%d",&sizeA);
	scanf("%d",&sizeB);
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
