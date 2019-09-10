#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
  
int main() 
{
    // ftok to generate unique key 
    key_t key = ftok("/home/oslab-22/33304/Assignment8",65);
    if(key == -1) {
    	printf("\nError while creating the key!\n");
    	exit(0);
    }
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    if(shmid < 0) {
    	printf("\nError while creating the shared memory!\n");
    	exit(0);
    } 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("\nEnter the string:");
    gets(str);
  
    printf("\nData written in memory: %s\n",str);
    printf("\nShared memory address: %X\n",shmid );

    //detach from shared memory  
    shmdt(str);
   	while(1);
    
    return 0;
} 
