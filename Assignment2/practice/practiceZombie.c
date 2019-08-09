#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid = getpid();
	printf("\nCURRENT PROCESS ID IS:%d \n",pid);
	
	printf("\n\nFORKING CHILD PROCESS!");
	pid = fork();
	
	if(pid < 0)
		exit(-1);					//Process failed
		
	else if (pid == 0)
	{
		printf("\nCHILD PROCESS STARTED:%d",getpid());
		printf("\nPARENT ID IS:%d",getppid());
		printf("\nCHILD PROCESS COMPLETED!");
		sleep(1);
		printf("\n\nI'M IN ZOMBIE STATE!\n");
	}
	
	else
	{
		sleep(10);
		printf("\n\nPARENT PROCESS STARTED:%d\n",getpid());
		wait(NULL);
	}
	return 0;
}

