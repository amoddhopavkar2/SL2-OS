#include <stdio.h>
#include <stdlib.h>
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

int main()
{
	int rows1,rows2,cols1,cols2;

	printf("\n\nENTER THE NO OF ROWS IN MATRIX A:");
	scanf("%d",&rows1);
	printf("\nENTER THE NO OF COLUMNS IN MATRIX A:");
	scanf("%d",&cols1);
	
	printf("\nENTER THE NO OF ROWS IN MATRIX B:");
	scanf("%d",&rows2);
	printf("\nENTER THE NO OF COLUMNS IN MATRIX B:");
	scanf("%d",&cols2);

	if(cols1 != rows2)
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

	printf("\n\nENTER THE NO FOR MATRIX A:\n");
	input(matA, rows1, cols1);

	printf("\n\nENTER THE NO FOR MATRIX B:\n");
	input(matB, rows2, cols2);

}