#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
	key_t fkey = ftok("/home/oslab-22/Desktop",65);			//ftok is used to generate a unique key
	if (fkey == -1) {										//Error if key creation fails
		printf("\nERROR IN CREATING THE KEY!");
		exit(0);
	}

	int shmID = shmget(fkey,1024,0666|IPC_CREAT);			//shmget returns a unique identifier in shmID
	if (shmID == -1) {										//Error if shared memory creation fails
		printf("\nERROR IN CREATING THE SHARED MEMORY!");
		exit(0);
	}

	char *str = (char*) shmat(shmID,(void *)0,0);			//shmat used to attach to the shared memory
	printf("\nENTER THE STRING: ");
	fgets(str,100,stdin);

	printf("\nDATA WRITTEN IN THE SHARED MEMORY: %s\n",str);			
	printf("\nSHARED MEMORY ADDRESS: %X\n",shmID);

	shmdt(str);												//shmdt used to detach from the shared memory
	while(1);
	return 0;
}