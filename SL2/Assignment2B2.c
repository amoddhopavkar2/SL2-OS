#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

int main(int argc, char *argv[]) {
	int arr[SIZE], key, i;
	printf("\nENTER A NUMBER:");
	scanf("%d",&key);
	for (i=0; i<argc; i++)
		arr[i] = atoi(argv[i]);

	int left = 0, right = i-1, mid, flag;
	while(left <= right) {
		mid = (left + right)/2;
		if (key == arr[mid]) {
			flag = 1;
			break;
		}

		else if (key < arr[mid]){
			right = mid -1;
		}

		else {
			left = mid + 1;
		}
	}

	if (flag == 1) {
		printf("\nNUMBER '%d' FOUND AT POSITION %d",key,mid+1);
	} 

	else {
		printf("\nNUMBER '%d' NOT FOUND!",key);
	} 

	return 0;
}