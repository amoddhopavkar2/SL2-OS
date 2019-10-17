#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define SIZE 20

void bubble_sort(int arr[], int n) {
	for (int i=0; i<n-1; i++) {
		for (int j=0; j<n-i-1; j++) {
			if (arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main() {
	pid_t pid;
	int arr[SIZE], n, i;
	char str[SIZE], *arg[SIZE];
	printf("\nENTER NO OF ELEMENTS:");
	scanf("%d",&n);
	printf("\nENTER THE ELEMENTS:\n");
	for (i=0; i<n; i++)
		scanf("%d",&arr[i]);

	printf("\nIN MAIN PROCESS...");
	printf("\nMAIN PROCESS ID:%d",getpid());
	printf("\n\nSORTING THE NUMBERS...\n");
	bubble_sort(arr,n);

	printf("\nINVOKING FORK...");
	pid = fork();
	
	if (pid > 0) {
		printf("\n\nIN PARENT PROCESS...");
		wait(NULL);
		printf("\nPARENT EXITS...\n");
	}

	else {
		printf("\nIN CHILD PROCESS...");
		printf("\nCHILD PROCESS ID:%d",getpid());
		printf("\nPARENT PROCESS ID:%d",getppid());
		printf("\n\nTHE SORTED NUMBERS ARE...\n");
		for (i=0; i<n; i++) {
			printf("%d\t",arr[i]);
			sprintf(str,"%d",arr[i]);
			arg[i] = malloc(sizeof(str));
			strcpy(arg[i],str);
		}
		arg[i] = NULL;
		printf("\n\nEXECUTING THE 2nd PROGRAM...");
		execve("./2B2",arg,NULL);
		printf("\nCHILD EXITS...\n");
	}
}