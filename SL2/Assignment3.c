#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define SIZE 10

int matA[SIZE][SIZE], matB[SIZE][SIZE], matC[SIZE][SIZE];

void input(int mat[SIZE][SIZE], int rows, int cols) {
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			printf("\nENTER THE NO IN LOCATION [%d][%d]:",i+1,j+1);
			scanf("%d",&mat[i][j]);
		}
	}
}

void display(int mat[SIZE][SIZE], int rows, int cols) {
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			printf("%d\t",mat[i][j]);
		}
		printf("\n");
	}
}

void *mulThread(void *arg) {
	int rows, cols, *argZ, num, sum = 0, flag = 0;
	argZ = (int *)arg;
	rows = argZ[0];
	cols = argZ[1];
	num = argZ[2];

	printf("\n\nTHREAD %d-%d JOINED...",rows+1,cols+1);
	for (int i=0; i<num; i++) {
		sum += matA[rows][i] * matB[i][cols];
		printf("\n%d --> THREAD %d-%d CALCULATED %d*%d = %d\t%d",flag,rows+1,cols+1,matA[rows][i],matB[i][cols],matA[rows][i]*matB[i][cols],sum);
		printf("\n%d --> THREAD %d-%d PAUSED...",flag,rows+1,cols+1);
		int sleepTime = rand()%7;
		printf("\nSLEEPING FOR %d SECONDS...",sleepTime);
		sleep(sleepTime);
		printf("\n%d --> THREAD %d-%d RESUMES...",flag,rows+1,cols+1);
		flag++;
	}
	printf("\n\nTHREAD %d-%d EXITS...",rows+1,cols+1);
	pthread_exit((void *)sum);
}

int main() {
	int rowsA, colsA, rowsB, colsB, arg[3], *status;
	pthread_t P[SIZE][SIZE];

	printf("\nNO. OF ROWS IN MATRIX A:");
	scanf("%d",&rowsA);
	printf("\nNO. OF COLUMNS IN MATRIX A:");
	scanf("%d",&colsA);

	printf("\nNO. OF ROWS IN MATRIX B:");
	scanf("%d",&rowsB);
	printf("\nNO. OF COLUMNS IN MATRIX B:");
	scanf("%d",&colsB);

	while (colsA != rowsB) {
		printf("\nMULTIPLICATION NOT POSSIBLE! RE-ENTER COMPATIBLE ROWS AND COLUMNS");
		printf("\nNO. OF ROWS IN MATRIX A:");
		scanf("%d",&rowsA);
		printf("\nNO. OF COLUMNS IN MATRIX A:");
		scanf("%d",&colsA);

		printf("\nNO. OF ROWS IN MATRIX B:");
		scanf("%d",&rowsB);
		printf("\nNO. OF COLUMNS IN MATRIX B:");
		scanf("%d",&colsB);
	}

	printf("\n\nNO's IN MATRIX A:\n");
	input(matA, rowsA, colsA);
	printf("\n\nNO's IN MATRIX B:\n");
	input(matB, rowsB, colsB);

	printf("\n\nMATRIX A:\n");
	display(matA, rowsA, colsA);
	printf("\n\nMATRIX B:\n");
	display(matB, rowsB, colsB);

	for (int i=0; i<rowsA; i++) {
		for (int j=0; j<colsB; j++) {
			arg[0] = i;
			arg[1] = j;
			arg[2] = colsA;

			if (pthread_create(&P[i][j],NULL,mulThread,arg) != 0) {
				printf("\nERROR IN THREADING...");
			}

			else {
				printf("\nTHREAD %d - %d CREATED...",i+1,j+1);
				sleep(2);
			}
		}
	}

	for (int i=0; i<rowsA; i++) {
		for (int j=0; j<colsB; j++) {
			if (pthread_join(P[i][j],(void **) &status) != 0){
				printf("\nERROR IN THREAD JOINING...");
			}

			matC[i][j] = (int)status;
		}
	}

	printf("\n\nRESULTANT MATRIX:\n");
	display(matC,rowsA,colsB);
	printf("\n");
	return 0;
}