#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bubbleSort(int arr[],int n)
{
	int i,j,temp;
	for(i=0; i<n-1; i++)
		for(j=0; j<n-i-1; j++)
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp; 	
			}	
}

int main()
{
	int pid,n,i,arr[20];
	char *arg[15],str[20];
	printf("\nNUMBER OF ENTRIES: ");
	scanf("%d",&n);
	printf("\nENTER THE NUMBERS:\n");
	for(i=0; i<n; i++)
		scanf("%d",&arr[i]);

	printf("\nMAIN PROCESS ID:%d\n",getpid() );
	printf("\nSORTING THE NUMBERS...\n");
	bubbleSort(arr,n);
	printf("SORTING COMPLETED!\n");
	
	printf("\nINVOKING FORK....\n");
	pid = fork();

	if(pid == 0)
	{
		printf("\nCHILD PROCESS ID IS:%d\n",getpid() );
		printf("PARENT PROCESS ID IS:%d\n",getppid() );
		printf("\nTHE SORTED NUMBERS ARE: ");
		for(i=0; i<n; i++)
		{
			printf("%d  ",arr[i]);
			sprintf(str,"%d",arr[i]);
			arg[i] = malloc(sizeof(str));
			strcpy(arg[i],str);
		}
		arg[i] = NULL;
		printf("\n\nEXECUTING THE 2nd PROGRAM!");
		execve("./2b2",arg,NULL);
		printf("\n2nd PROGRAM EXECUTED!\n");
		printf("\nCHILD PROCESS COMPLETED. CHILD EXITS!\n");
	}

	else if(pid > 0)
	{
		printf("\n\nIN PARENT PROCESS!\n");
		printf("WAITING...\n");
		wait();
		printf("\nPARENT PROCESS COMPLETED. PARENT EXITS!\n");
	}

	else if(pid < 0)
		printf("\n\nCHILD NOT CREATED!\n");

	return 0;
}
