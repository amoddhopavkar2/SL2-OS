#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
	key_t fkey = ftok("/home/oslab-22/Desktop",65);		//ftok is used to generate a unique key
	if (fkey == -1) {									//Error in key creation
		printf("\nERROR IN CREATING THE KEY!");
		exit(0);
	}
	
	int shmID = shmget(fkey,1024,0666|IPC_CREAT);		//shmget returns a unique identifier in shmID
	if (shmID == -1) {									//Error in shared memory creation
		printf("\nERROR IN CREATING SHARED MEMORY");
		exit(0);
	}

	char *str = (char*) shmat(shmID,(void *)0,0);		//shmat used to attach to the shared memory
	printf("\nDATA READ FROM THE SHARED MEMORY: %s\n",str);
	printf("\nSHARED MEMORY ADDRESS: %X\n",shmID);

	shmdt(str);											//shmdt used to detach from the shared memory
	shmctl(shmID,IPC_RMID,NULL);						//shmctl used to destroy the shared memory

	return 0;
}
