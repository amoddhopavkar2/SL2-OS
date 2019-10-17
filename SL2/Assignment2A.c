#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define SIZE 20

void bubble_sort_ascending(int arr[], int n) {
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

void bubble_sort_descending(int arr[], int n) {
	for (int i=0; i<n-1; i++) {
		for (int j=0; j<n-i-1; j++) {
			if (arr[j] < arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main () {
	pid_t pid;
	int arr[SIZE], n;
	printf("\nENTER NO OF ELEMENTS:");
	scanf("%d",&n);
	printf("\nENTER THE ELEMENTS:\n");
	for (int i=0; i<n; i++)
		scanf("%d",&arr[i]);

	pid = fork();
	if (pid < 0) {
		printf("\nERROR IN FORKING!");
		exit(1);
	}

	else if (pid > 0) {
		printf("\nIN PARENT PROCESS...\n");
		printf("\nBUBBLE SORT IN ASCENDING ORDER...\n");
		bubble_sort_ascending(arr,n);
		wait(NULL);
		printf("\nSORTING COMPLETED!\n");
		for (int i=0; i<n; i++)
			printf("%d\t",arr[i]);
		printf("\nCHILD EXITED...");
		printf("\nPARENT PROCESS EXITS...\n");
	}

	else {
		printf("\nIN CHILD PROCESS...\n");
		printf("\nBUBBLE SORT IN DESCENDING ORDER...\n");
		bubble_sort_descending(arr,n);
		printf("\nSORTING COMPLETED!\n");
		for (int i=0; i<n; i++)
			printf("%d\t",arr[i]);
		printf("\nEXITING CHILD PROCESS...");
	}

	return 0;
}