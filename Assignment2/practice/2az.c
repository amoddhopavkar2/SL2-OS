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

	printf("\n\nThe sorted list is: ");
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
		
	else if(pid == 0)
	{
		printf("Child process is running!\n");
		printf("Child process ID: %d\n",getpid() );
		printf("Parent process ID: %d\n",getppid() );
	}
		
	else
	{
		printf("\nParent process ID:%d\n",getpid());

		bubbleSort(arr,n);

		printf("\nParent process is running!\n");
		sleep(10);
		wait(NULL);
	}
}