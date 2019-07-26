#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define max 20

void quickSort(int arr[max], int, int);
int partition(int arr[max], int, int);

void bubbleSort(int arr[max], int);

int main()
{
	int i,arrQuick[max],arrBubble[max],quick,bubble;
	printf("\nEnter the number of elements for Quick Sort:");
	scanf("%d",&quick);
	printf("\nEnter the elements:\n");
	for(i=0; i<quick; i++)
		scanf("%d",&arrQuick[i]);

	printf("\n\nEnter the number of elements for Bubble Sort:");
	scanf("%d",&bubble);
	printf("\nEnter the elements:");
	for(i=0; i<bubble; i++)
		scanf("%d",&arrBubble[i]);

	int pid = fork();

	if(pid == 0)
	{
		printf("\nIn child process...\nID:%d",getpid());
		printf("\nParent process ID is:%d",getppid());
		sleep(10);
		quikSort(arrQuick,0,quick-1);
		printf("\n\nQuick Sort completed!\n");
		for(i=0; i<quick; i++)
			printf("%d  ",arrQuick[i]);
		printf("\n\nChild Process completed!\n");
	}

	else
	{
		printf("\nIn parent process...\nID:%d",getpid());
		printf("\nPerforming Bubble Sort on the array...\n");
		bubbleSort(arrBubble,bubble);
		printf("\n\nBubble Sort completed!\n");
		for(i=0; i<bubble; i++)
			printf("%d  ",arrBubble[i]);
		printf("\n");
		wait();
		printf("\n\nChild completed it's execution...");
		printf("\nNow parent free to exit...\n");
		exit(0);
	}
	return 0;
}

void quikSort(int arr[max], int l, int r)
{
	int i;
	if(l < r)
	{
		i = partition(arr,l,r);
		quikSort(arr,l,i-1);
		quikSort(arr,i+1,r);
	}
}

int partition(int arr[max], int l, int r)
{
	int i,j,v,temp;
	v = arr[l];
	i = l;
	j = r+1;

	do
	{
		do
		i++;
		while (arr[i] < v && i <= r);

		do
		j--;
		while (v < arr[j]);

		if(i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

	}
	while (i < j);

	arr[l] = arr[j];
	arr[j] = v;
	return j;
}

void bubbleSort(int arr[],int n)
{
	int i;
	for(int i=0; i<n-1; i++)
		for(int j=0; j<n-i-1; j++)
			if(arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp; 	
			}
}