#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

	printf("\nThe sorted list is: ");
	for(i=0; i<n; i++)
		printf("%d ",arr[i]);		
}

void main()
{
	int n,pid,i,arr[100];
	printf("\nNumber of elements in parent process:");
	scanf("%d",&n);
	
	printf("\nEnter the elements:\n");
	for(i=0; i<n; i++)
		scanf("%d",&arr[i]);

	i = 0;
	pid = fork();

	if(pid < 0)
		printf("Child not created!\n");

	else if (pid == 0)
	{
		printf("Child process is running!\n");
		printf("Child process ID:%d\n",getpid() );

		bubbleSort(arr,n);

		printf("\nOld parent ID:%d\n",getppid() );
		sleep(10);
		printf("\nNew parent ID:%d\n",getppid() );
	}

	else
	{
		printf("\nParent process running!\n");

		bubbleSort(arr,n);

		printf("\nParent process ID:%d\n",getpid() );
	}
}