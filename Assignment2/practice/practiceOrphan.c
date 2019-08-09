#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 

void main()
{
	int id = fork();

	if(id == 0)
	{
		printf("\nThe child process has started!\n");
		printf("Child process id is:%d \n",getpid() );
		printf("Child process parent id is:%d \n",getppid() );
		printf("Child goes to sleep!\n");
		sleep(10);

		printf("\nOrphan child id is:%d \n",getpid() );
		printf("Orphan child parent id is:%d \n",getppid() );
		exit(0);
	}

	else
	{
		printf("The parent process has started!\n");
		printf("Parent process id is:%d \n",getpid() );
		printf("Parent goes to sleep!\n");
		sleep(5);
		exit(0);
	}
}