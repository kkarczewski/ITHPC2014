#include <stdio.h>
#include <stdlib.h>
#include <math.h> //z flagą -lm na końcu polecenia
#include <time.h> //z flagą -lrt
//KOMPILACJA gcc macierz.c -lrt -lm
int main(){
	int j,l;//zmienne pomocnicze
	int size=0;//wielkość macierzy
	int i=0;
	clock_t start, stop;
	double timeI,timeO,timeZ;
	FILE *plik;
	int *A;//macierz
//POCZĄTEK POMIARU DLA IO;
	start=clock();
	if((plik=fopen("dane.txt","r"))==0){
		printf("Nie mogę otworzyć pliku\n");
	}
	//printf("Otworzyłem plik\n");
	while(fscanf(plik,"%d",&l)!=EOF){
		size++;
	}
	//printf("Plik zawiera %d liczb.\n",size);
//rezerwacja pamięci na macierz
	A = (int*)malloc(sizeof(int)*size);	
	//printf("Zająłem miejsce dla A\n");
	rewind(plik);
	while(fscanf(plik,"%d",&A[i])!=EOF){
		i++;
	}

//Wydruk testowy A
	//for(i=0;i<size;i++){
	//	printf("A[%d]=%d, ",i,A[i]);	
	//}
	int temp; //wielkość wektora
	temp=sqrt(size);
	//printf("temp=%d \n",temp);
//WEKTOR
	//WYGENEROWAĆ WEKTOR RANDEM DO TABLICY OD TEMP BEZ OTWIERANIA PLIKU
	//PORÓWNAĆ CZASY!!!
	int *B, *C;//wektor i wynik
	if((plik=fopen("wektor.txt","r"))==0){
		printf("Nie mogę otworzyć pliku\n");
	}
	//printf("Otworzyłem plik WEKTOR\n");
	B = (int*)malloc(sizeof(int)*temp);	//wektor
	C = (int*)malloc(sizeof(int)*temp); //wynik
	i=0;
	while(fscanf(plik,"%d",&B[i])!=EOF){
		i++;
	}
//KONIEC POMIARU IO
	stop=clock();
	timeI=(double)(stop-start)/(CLOCKS_PER_SEC);
	printf("Czas wczytania plików=%2.5f\n",timeI);
//Wydruk testowy B
	//for(i=0;i<temp;i++){
	//	printf("%d ",B[i]);
	//}
//mnożenie c[0]=a[0][0]*b[0]+a[0][1]*b[1]+...+a[0][j]*b[j]+...+a[0][n]*b[n]
//		   c[i]=a[i][0]*b[0]+a[i][1]*b[1]+...+a[i][j]*b[j]+...+a[0][n]*b[n]
//		   c[n]=a[n][0]*b[0]+a[n][1]*b[1]+...+a[n][j]*b[j]+...+a[n][n]*b[n]
//n=size
//POCZĄTEK POMIARU DLA OBLICZEŃ;
	start=clock();
	for(i=0;i<temp;i++){
		for(j=0;j<temp;j++){
			C[i]+=A[j*temp+i]*B[j];
		}
	}
//KONIC POMIARU DLA OBLICZEŃ
	stop=clock();
	timeZ=(double)(stop-start)/(CLOCKS_PER_SEC);
	printf("Czas obliczeń %2.5f\n",timeZ);

//Wydruk wektora
	start=clock();
	for(i=0;i<temp;i++){
		printf("%d ",C[i]);
	}
	printf("\n");
	stop=clock();
	timeO=(double)(stop-start)/(CLOCKS_PER_SEC);
//WYDRUK CZASÓW
	printf("Czas wczytania: %2.2f s\n",timeI);
	printf("Czas obliczeń: %2.2f s\n",timeZ);
	printf("Czas zapisu: %2.2f s\n",timeO);
	printf("Czas operacji IO=%2.2f s\n",timeI+timeO);
	printf("Czas całkowity=%2.2f s\n",timeI+timeO+timeZ);
//uwolnienie pamięci, zamknięcie pliku
	free(A);
	free(B);
	free(C);
	fclose(plik);
	return 0;
}
