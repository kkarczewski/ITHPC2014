#include <stdio.h>
#include <stdlib.h>
int main(){
	int i,size;
	scanf("%d",&size);
	int* B = (int*)malloc(sizeof(int*)*size);	
	srand(1);
	for(i=0;i<size;i++){
		B[i]=rand()%10;
	}
	for(i=0;i<size;i++){
		printf("%d ",B[i]);
	}
	return 0;
	free(B);
}
