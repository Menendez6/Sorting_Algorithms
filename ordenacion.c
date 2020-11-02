//Esqueleto
/*
 * Práctica 1:  Algoritmo de ordenación tipo B + Sacudida +Shell
 * Autor:       Pablo Menéndez Ruiz de Azúa
 * Fecha:       02/11/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

//Compruebo el OS
#ifdef _WIN32
#define OS "WIN"
#elif defined __unix__
#define OS "LINUX"
#elif defined __APPLE__
#define OS "MAC"
#endif


#define F50 "C:\\Users\\pablo\\Algoritmica\\50numerosdesordenados.txt"
#define F500 "C:\\Users\\pablo\\Algoritmica\\500numerosdesordenados.txt"
#define F1000 "C:\\Users\\pablo\\Algoritmica\\1000numerosdesordenados.txt"
#define F5000 "C:\\Users\\pablo\\Algoritmica\\5000numerosdesordenados.txt"
#define F100000 "C:\\Users\\pablo\\Algoritmica\\100000numerosdesordenados.txt"
#define F1000000 "C:\\Users\\pablo\\Algoritmica\\1000000numerosdesordenados.txt"
#define FILE_SALIDA "C:\\Users\\pablo\\Algoritmica\\salida.txt"
#define NUM_EJE 10
#define TIP_EJE 5
#define NUM_FICHERO 5
#define TAM_CAD 100
#define NUM_MET 7
#define NUM_BUCKET 10
#define NUM_INT 32767

typedef struct {
	int count;
	int *value;
} T_BUCKET;

//Prototipo de funciones
void CargaFichero(FILE *, int[], int);
void MostrarVector(int[], int);
void LimpiarBuffer();
void InserccionDirecta(int[], int);
//void MezclaDirecta(int[], int[], int,int);
//void Mezclar(int [], int [], int, int, int);
void Burbuja(int[], int);
void Sacudida(int[], int);
void Shell(int[], int);
void Heapsort(int[], int);
void MonticuloInicial(int[],int);
void Monticuliza(int[],int,int);
int Padre(int);
int Hijo_izq(int);
int Hijo_der(int);
void Quicksort(int [],int,int);
int Divide (int[],int,int);
int SeleccionUmbral(int [],int,int);
void Bucketsort(int [],int);
int Maximo(int [],int);

int main(int argc, char **argv)
{
	FILE *fp; //Fichero para manejar los ficheros
    FILE *fsalida; //Puntero a fichero para manejar salidas
    int tipoSalida=0; //tipoSalida --> 0 mixta, 1 sólo pantalla
	int v[100000];
	//int aux[5000];
	long int ejecucion[TIP_EJE];
	char file_ejecucion[TIP_EJE][TAM_CAD];
	char metodos[NUM_MET][TAM_CAD];

	//Variables para medir el tiempo
	clock_t start, end;
	double resultados[NUM_MET][TIP_EJE];
	//Variables auxiliares
	int i,j,k;
	char opc;

	//Carga por defecto la información
	ejecucion[0]=50;
	ejecucion[1]=500;
	ejecucion[2]=1000;
	ejecucion[3]=5000;
    ejecucion[4]=100000;
    //ejecucion[5]=1000000; Con un millón de datos no me deja ni con el comando: C:\TDM-GCC-64\bin\gcc.exe -Wl,--stack,1073741824 -o fichero.exe "C:\Program Files\CodeLite\Algoritmica\Practicas\ordenacion\ordenacion.c"
	
	strcpy(file_ejecucion[0],F50);
	strcpy(file_ejecucion[1],F500);
	strcpy(file_ejecucion[2],F1000);
	strcpy(file_ejecucion[3],F5000);
    strcpy(file_ejecucion[4],F100000);
    //strcpy(file_ejecucion[5],F1000000);

	strcpy(metodos[0],"Insercción Directa");
	//strcpy(metodos[1],"Mezcla Directa");
	strcpy(metodos[1],"Burbuja");
	strcpy(metodos[2],"Sacudida");
	strcpy(metodos[3],"Shell");
	strcpy(metodos[4],"Heapsort");
	strcpy(metodos[5],"Quicksort");
	strcpy(metodos[6],"Bucketsort");

	printf("\nDesea visualizar los vectores: (S/N): ");
	LimpiarBuffer();
	scanf("%c",&opc);
	//opc=toupper(opc);

	 /*fp=fopen("C:\\Users\\pablo\\Algoritmica\\1000000numerosdesordenados.txt","r");
	 CargaFichero(fp,v,1000000);
	 MostrarVector(v, 1000000);
	 Bucketsort(v,1000000);	   
	 printf("==================");
	 MostrarVector(v, 1000000);
	 getchar();
	 getchar();*/
	 for(k=0; k<NUM_MET; k++) {

		printf("\n\t=============================");
		printf("\n\t       %s",metodos[k]);
		printf("\n\t=============================");
		for (i=0; i<NUM_FICHERO; i++) {
			printf("\n\t1.- Ejecucion con %4ld datos",ejecucion[i]);
			//Inicializo el temporizador
			resultados[k][i]=0;
			for(j=0; j<NUM_EJE; j++) {
				fp=fopen(file_ejecucion[i],"r");
				if (fp==NULL) {
					printf("\nError al abrir el fichero");
				} else {
					CargaFichero(fp,v,ejecucion[i]);
					if (opc=='S') {
						printf("\nPulsa enter para ver los datos");
						getchar();
						MostrarVector(v, ejecucion[i]);
						printf("\nFin de Datos");
						printf("\nEjecutando...");
					}
					start = clock();
					switch(k) {
					case 0:
						InserccionDirecta(v,ejecucion[i]);
						break;
					//case 1:
						//MezclaDirecta(v,aux,0,ejecucion[i]);
						//break;
					case 1:
						Burbuja(v,ejecucion[i]);
						break;
					case 2:
						Sacudida(v,ejecucion[i]);
						break;
					case 3:
						Shell(v,ejecucion[i]);
						break;
					case 4:
						Heapsort(v,ejecucion[i]);
						break;
					case 5:
						Quicksort(v,0,ejecucion[i]);
						break;
					case 6:
						Bucketsort(v,ejecucion[i]);
						break;
					default:
						printf("\nMetodo no encontrado");

					}
					end=clock();
					printf("\nEjecucion num %d, tiempo %f",j,((double) (end - start)) / CLOCKS_PER_SEC);
					resultados[k][i]+= ((double) (end - start)) / CLOCKS_PER_SEC;
					if (opc=='S') {
						printf("\nPulsa enter para ver los datos ordenados");
						getchar();
						MostrarVector(v, ejecucion[i]);
						getchar();
						printf("\nFin de ejecución");
					}
				}
			}
			printf("\nTiempo total: %f",resultados[k][i]);
			resultados[k][i]/=NUM_EJE;
			printf("\nTiempo medio: %f",resultados[k][i]);
            //getchar();
          
		}
        //printf("\nPulse enter para continuar: ");
        //getchar();
	}
	fsalida=fopen(FILE_SALIDA,"w");
    if (fsalida==NULL) {
        tipoSalida=1; //Hago que la salida sea solo por pantalla
        printf("\nError al abrir el fichero");
    } else {
        printf("\nFichero de salida abierto");
    }
    //Ahora imprimo la tabla resumen de resultados:
	printf("\n\n");
	printf("\n================================================================================");
	printf("\n|\tAlgoritmo\t\t|\tEjecucion\t|\tTiempo\t\t|");
	printf("\n================================================================================");
    if (tipoSalida==0) fprintf(fsalida,"Algoritmo,Ejecucion,Tiempo\n");
	for (i=0; i<NUM_MET; i++) {
		for (j=0; j<TIP_EJE; j++) {
			printf("\n|\t%s",metodos[i]);
			if(strlen(metodos[i])>16) {
				printf("\t|\t%7ld\t\t|\t%f\t\t|",ejecucion[j],resultados[i][j]);
			} else if (strlen(metodos[i])<8) {
				printf("\t\t\t|\t%7ld\t\t|\t%f\t\t|",ejecucion[j],resultados[i][j]);
			} else {
				printf("\t\t|\t%7ld\t\t|\t%f\t\t|",ejecucion[j],resultados[i][j]);
			}
            if (tipoSalida==0) fprintf(fsalida,"%s,%7ld,%f\n",metodos[i],ejecucion[j],resultados[i][j]);
		}        
	}    
	printf("\n================================================================================");
	LimpiarBuffer();
    getchar();
    if(tipoSalida==0) if (fclose(fsalida)!=0) printf("\nError al cerrar el fichero");
	return 0;
}

void LimpiarBuffer()
{

	if (strcmp(OS,"WIN")==0) {
		fflush(stdin);
	} else if (strcmp(OS,"LINUX")==0) {
		setbuf( stdin, NULL );
	}/*else if (strcmp(OS,"MAC")==0) {
        fpurge();
    }*/else {
		printf("\nError al Limpiar el buffer");
	}
}




void CargaFichero(FILE *fp, int v[], int limite)
{
	int i;
	int num;
	int ctrl;


	i=0; // Inicializo
	do {
		ctrl=fscanf(fp,"%d",&num);
		if (ctrl==1) {
			//Si he leido correctamente el fichero lo meto en el fichero
			v[i]=num;
			i++;
		}
	} while(ctrl==1 && i<limite);
}


void MostrarVector(int v[], int lim)
{
	int i;

	for (i=0; i<lim; i++) {
		printf("\n%d",v[i]);
	}
}



//----------- Hasta aquí --------------






//Algoritmo inserción directa
void InserccionDirecta(int A[], int N){
	int i;
	int j;
	int carta;
	
	for (i=1;i<N;i++){
		carta=A[i];
		j=i-1;
		while(j>-1 && carta<A[j]){
			A[j+1]=A[j];
			j=j-1;
		}
		A[j+1]=carta;
	}
}

//Algoritmo Burbuja
void Burbuja(int A[], int N){
	int i;
	int j;
	int x;
	
	for (i=1;i<N;i++){
		for (j=N;j>=i;j=j-1){
			if (A[j-1]>A[j]){
				x=A[j-1];
				A[j-1]=A[j];
				A[j]=x;
			}
		}
	}
}

// Sacudida

void Sacudida(int A[], int N){
	int iz=1;
	int de=N-1;
	int k=N-1;
	int j,x;
	
	while(de>=iz){
		for (j=de;j>=iz;j--){
			if (A[j-1]>A[j]){
				x=A[j-1];
				A[j-1]=A[j];
				A[j]=x;
				k=j;
			}
		}
		iz=k+1;
		for (j=iz;j<=de;j++){
			if (A[j-1]>A[j]){
				x=A[j-1];
				A[j-1]=A[j];
				A[j]=x;
				k=j;
			}
		}
		de=k-1;
	}
}

//Shell

void Shell(int A[], int N){
	int INC[4];
	int m,p,i,carta,j;
	
	INC[0]=9;
	INC[1]=5;
	INC[2]=3;
	INC[3]=1;
	
	for (m=0;m<4;m++){
		p=INC[m];
		for (i=p;i<N;i++){
			carta=A[i];
			j=i-p;
			while (j>=0 && carta<A[j]){
				A[j+p]=A[j];
				j=j-p;
			}
			A[j+p]=carta;
		}
	}
}

//HeapSort

void Heapsort(int A[], int N){
	int x;
	int i;
	
	MonticuloInicial(A,N);
	
	for (i=N-1;i>=0;i--){
		x=A[0];
		A[0]=A[i];
		A[i]=x;
		
		Monticuliza(A,i,0);
	}
}

void MonticuloInicial(int A[], int N){
	int Tam_Mont;
	int i;
	Tam_Mont=N;
	
	for (i=floor(N/2)-1;i>=0;i--){
		Monticuliza(A,Tam_Mont,i);
	}
}

void Monticuliza (int A[],int Tam_Mont, int i){
	int iz;
	int de;
	int mayor=i;
	int x;
	
	iz=2*i+1;
	de=2*i+2;
	
	if ((iz<Tam_Mont) && (A[iz]>A[mayor])){
		mayor=iz;
	}
	
	if ((de<Tam_Mont) && (A[de]>A[mayor])){
		mayor=de;
	}
	if (mayor != i){
		x=A[i];
		A[i]=A[mayor];
		A[mayor]=x;
		Monticuliza(A,Tam_Mont,mayor);
	}
}

//QuickSort

void Quicksort(int A[], int iz, int de){
	int d;
	
	if (iz<de){
		d=Divide(A,iz,de);
		Quicksort(A,iz,d);
		Quicksort(A,d+1,de);
		
	}
}

int Divide(int A[], int iz, int de) {
	int u;
	int i;
	int j;
	int x;
	int CONTINUAR;
	
	u=SeleccionUmbral(A,iz,de);
	i=iz;
	j=de;
	
	CONTINUAR = 1;
	while (CONTINUAR==1){
		while(A[i]<u){
			i=i+1;
		}
		while(A[j]>u){
			j=j-1;
		}
		if (i<j){
			x=A[i];
			A[i]=A[j];
			A[j]=x;
			i=i+1;
			j=j-1;
		}else{
			CONTINUAR=0;
		}
	}
	return j;
	
}


int SeleccionUmbral(int A[], int iz, int de){
	int u;
	
	u=A[iz];
	return u;	
}


//BucketSort
void Bucketsort(int A[], int N){
	int k=NUM_BUCKET;
	T_BUCKET bucket[k];
	int mayor;
	int div;
	int i;
	int cubo;
	int suma[k];
	int pos;
	int cont;
	int sum;
	
	
	mayor = Maximo(A,N);
	
	div=(mayor+1)/k+1; 
	printf("\n %d",div);
	
	//Inicicalizamos los tamaños de cada bucket
	for (i=0;i<k;i++){
		bucket[i].count=0;
	}
	
	//Hallamos el tamaño de cada bucket
	for (i=0;i<N;i++){
		cubo=floor(A[i]/div);
		bucket[cubo].count++;
	}
	
	//Inicializamos cada vector de los buckets
	for (i=0;i<k;i++){
		bucket[i].value=(int *)calloc(bucket[i].count,sizeof(int));
	}
	
	for (i=0;i<k;i++){
		if (bucket[i].value==NULL){
			printf("Error en la asignacion de memoria");
		}
	}
	
	//Inicializamos el vector que va a ir contando los sitios
	for (i=0;i<k;i++){
		suma[i]=0;
	}
	
	
	//Añadimos los elementos a cada bucket
	for (i=0;i<N;i++){
		cubo=floor(A[i]/div);
		pos=suma[cubo];
		bucket[cubo].value[pos]=A[i];
		suma[cubo]++;
	}
	
	
	//Ordenamos cada bucket por insercion directa
	for (i=0;i<k;i++){
		InserccionDirecta(bucket[i].value,bucket[i].count);
	}
	
	//Lo volvemos a juntar en A
	cont=0;
	for (i=0;i<k;i++){
		for(sum=0;sum < bucket[i].count;sum++){
			A[cont]=bucket[i].value[sum];
			cont++;
		}
	}
	
}
 


int Maximo(int A[], int N){
	int mayor=0;
	for (int i=0; i<N; i++){
		if (A[i]>mayor){
			mayor=A[i];
		}
	}
	return mayor;
}
