#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define max 10

int matA[max][max], matB[max][max], matC[max][max];

void input(int mat[max][max], int rows, int cols)
{
	int i,j;
	for(i=0;i <rows; i++)
		for(j=0; j<cols; j++)
		{
			printf("\nENTER THE VALUE AT [%d][%d]:",i+1,j+1);
			scanf("%d",&mat[i][j]);
		}
}
	
void display(int mat[max][max], int rows, int cols)
{
	int i,j;
	printf("\n");
	for(i=0; i<rows; i++)
	{
		for(j=0; j<cols; j++)
			printf("%d ",mat[i][j]);
		printf("\n");
	}
}

void *mulThread(void *arg)
{
	int rows,cols,*argZ,num,sum=0,flag=0;
	argZ = (int *)arg;
	rows = argZ[0];
	cols = argZ[1];
	num = argZ[2];

	printf("\n\nTHREAD %d-%d JOINED:",rows+1,cols+1);
	for(int i=0; i<num; i++)
	{
		sum += matA[rows][i] * matB[i][cols];
		printf("\n%d --> THREAD %d-%d CALCULATED %d*%d = %d\t%d",flag,rows+1,cols+1,matA[rows][i],matB[i][cols],matA[rows][i]*matB[i][cols],sum);
		int sleepTime = rand()%10;
		printf("\n%d --> THREAD %d-%d PAUSED...",flag,rows+1,cols+1);
		printf("SLEEPING FOR %d secs...",sleepTime);
		sleep(sleepTime);
		printf("\n%d --> THREAD %d-%d RESUMED",flag,rows+1,cols+1);
		flag++;
	}
	printf("\n\nTHREAD %d-%d EXITS!",rows+1,cols+1);
	pthread_exit((void *)sum);
}

int main()
{
	int i,j,rows1,rows2,cols1,cols2,argC[3];
	int *status;
	pthread_t P[max][max];

	printf("\n\nENTER THE NO OF ROWS IN MATRIX A:");
	scanf("%d",&rows1);
	printf("\nENTER THE NO OF COLUMNS IN MATRIX A:");
	scanf("%d",&cols1);
	
	printf("\nENTER THE NO OF ROWS IN MATRIX B:");
	scanf("%d",&rows2);
	printf("\nENTER THE NO OF COLUMNS IN MATRIX B:");
	scanf("%d",&cols2);

	while(cols1 != rows2)
	{
		printf("\nMATRIX MULTIPLICATION NOT POSSIBLE!\n");
		printf("\nRE-ENTER VALID ROWS AND COLUMNS...\n");

		printf("\n\nENTER THE NO OF ROWS IN MATRIX A:");
		scanf("%d",&rows1);
		printf("\nENTER THE NO OF COLUMNS IN MATRIX A:");
		scanf("%d",&cols1);
		
		printf("\nENTER THE NO OF ROWS IN MATRIX B:");
		scanf("%d",&rows2);
		printf("\nENTER THE NO OF COLUMNS IN MATRIX B:");
		scanf("%d",&cols2);
	}

	printf("\n\nENTER THE NO's FOR MATRIX A:\n");
	input(matA, rows1, cols1);

	printf("\n\nENTER THE NO's FOR MATRIX B:\n");
	input(matB, rows2, cols2);

	for(i=0; i<rows1; i++)
	{
		for(j=0; j<cols1; j++)
		{
			argC[0] = i;
			argC[1] = j;
			argC[2] = cols1;
			if(pthread_create(&P[i][j],NULL,mulThread,argC) != 0)
				printf("\n\nERROR... CANNOT CREATE THREAD!");
			else
			{
				printf("\nTHREAD %d-%d CREATED!",i+1,j+1);
				sleep(3);
			}
		}
	}

	printf("\n\nMATRIX A:\n");
	display(matA,rows1,cols1);
	printf("\n\nMATRIX B:\n");
	display(matB,rows2,cols2);

	for(i=0; i<rows1; i++)
	{
		for(j=0; j<cols2; j++)
		{
			if(pthread_join(P[i][j],(void **) &status) != 0)
				printf("\nTHREAD JOINING FAILED!\n");
			matC[i][j] = (int)status;
		}
	}

	printf("\n\nRESULTANT MATRIX:\n");
	display(matC,rows1,cols2);
	printf("\n");
	exit(0);
}
