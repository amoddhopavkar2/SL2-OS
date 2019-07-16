#include <stdio.h>

int main(int argc, char *argv[])
{
	int arr[20],i,key;
	int mid,flag=0;
	printf("\nENTER THE NUMBER TO BE SEARCHED:");
	scanf("%d",&key);
	for(i=0; i<argc; i++)
		arr[i] = atoi(argv[i]);
	
	int l=0,r=i-1;
	while(l <= r)
	{
		mid = (l+r)/2;
		if(key == arr[mid])
		{
			flag = 1;
			break;
		}

		else if(key < arr[mid])
			r = mid-1;
		
		else
			l = mid+1;
	}
	if(flag == 0)
		printf("\n\nTHE NUMBER %d NOT FOUND!\n",key);
	else
		printf("\n\nTHE NUMBER %d FOUND AT POSITION %d !\n",key,mid+1);

	return 0;
}
	

	