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
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("\nEnter the string:");
    gets(str); 
  
    printf("Data written in memory: %s\n",str);

    while(*str != '*') {
    	sleep(1);
    }

    //detach from shared memory  
    shmdt(str);
    
    return 0;
} 
