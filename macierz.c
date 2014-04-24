#include <stdio.h>
#include <stdlib.h>
#include <time.h> //z flagą -lrt
#include <omp.h> // z flagą -fopenmp
//KOMPILACJA gcc macierz.c -fopenmp -lrt
int main(int argc, char *argv[]){
	int j,l;//zmienne pomocnicze
	int sizeA=atoi(argv[1]);//szerokość macierzy
	int sizeB=atoi(argv[2]);//wysokość macierzy
	int i=0;
	double timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p) {
        double diff =
            (((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
             ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec));
        return diff / 1000000000;
    }
    struct timespec start, end;
	double timeI,timeO,timeZ;
	FILE *plik;
	int *A;//macierz
//POCZĄTEK POMIARU DLA IO;
	clock_gettime(CLOCK_MONOTONIC, &start);
	if((plik=fopen("dane.txt","r"))==0){
		printf("Nie mogę otworzyć pliku\n");
	}
//rezerwacja pamięci na macierz
	A = (int*)malloc(sizeA*sizeB*sizeof(int*));	
	while(fscanf(plik,"%d",&A[i])!=EOF){
		i++;
	}
//WEKTOR
	int *B, *C;//wektor i wynik
	if((plik=fopen("wektor.txt","r"))==0){
		printf("Nie mogę otworzyć pliku\n");
	}
	//printf("Otworzyłem plik WEKTOR\n");
	B = (int*)malloc(sizeof(int)*sizeA);	//wektor
	C = (int*)malloc(sizeof(int)*sizeA); //wynik
	i=0;
	while(fscanf(plik,"%d",&B[i])!=EOF){
		i++;
	}

//KONIEC POMIARU IO
	clock_gettime(CLOCK_MONOTONIC, &end);
	timeI=timespecDiff(&end, &start);
//mnożenie c[0]=a[0][0]*b[0]+a[0][1]*b[1]+...+a[0][j]*b[j]+...+a[0][n]*b[n]
//		   c[i]=a[i][0]*b[0]+a[i][1]*b[1]+...+a[i][j]*b[j]+...+a[0][n]*b[n]
//		   c[n]=a[n][0]*b[0]+a[n][1]*b[1]+...+a[n][j]*b[j]+...+a[n][n]*b[n]
//POCZĄTEK POMIARU DLA OBLICZEŃ;
	clock_gettime(CLOCK_MONOTONIC, &start);
int temp=0;
	//#pragma omp parallel for private(i,j), reduction(+ : temp)
	#pragma omp parallel for default(shared) private(temp,i,j)  
	for(i=0;i<sizeA;i++){
		for(j=0;j<sizeB;j++){
			C[i]+=A[i*sizeA+j]*B[i];
		}
//		C[i]=temp;
	}
//KONIC POMIARU DLA OBLICZEŃ
	clock_gettime(CLOCK_MONOTONIC, &end);
	timeZ=timespecDiff(&end, &start);
	//printf("Czas obliczeń %2.5f\n",timeZ);

//Wydruk wektora
	clock_gettime(CLOCK_MONOTONIC, &start);
#pragma omp parallel for	
	for(i=0;i<sizeB;i++){
		printf("%d ",C[i]);
	}
	printf("\n");
	clock_gettime(CLOCK_MONOTONIC, &end);
	timeO=timespecDiff(&end, &start);
//WYDRUK CZASÓW
	printf("Czas wczytywania:  %.10f s\n",timeI);
	printf("Czas obliczeń: %.10f s\n",timeZ);
	printf("Czas zapisu: %.10f s\n",timeO);
	printf("Czas operacji IO=%.10f s\n",timeI+timeO);
	printf("Czas całkowity=%.10f s\n",timeI+timeO+timeZ);
//uwolnienie pamięci, zamknięcie pliku
	free(A);
	free(B);
	free(C);
	fclose(plik);
	return 0;
}
