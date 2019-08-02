#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
	
sem_t full,empty;					//Declaring semaphores
pthread_mutex_t mutex;				//Declaring mutex
int n, *buffer, count = 0;

void *producer(void *args) {			//Will pass no of arguments;
	int pos = *(int *)args;
	while(TRUE) {
		int sleepTime = rand()%7;
		sleep(sleepTime);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
				//Critical Section	
				printf("\n\nIN PRODUCER....",pos);
				int producerVal = rand()%222;
				printf("\nProducer generated a value:",producerVal);
				buffer[count] = producerVal;
				count++;
				sleep(1);
				printf("\nValues in Buffer:");
				for(int i=0; i<n; i++) {
					printf("%d\t",buffer[i]);
				}
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
	pthread_exit(NULL);
}

void *consumer(void *args) {			//Will pass no of arguments
	int pos = *(int *)args;
	while(TRUE) {
		int sleepTime = rand()%7;
		sleep(sleepTime);
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
				//Critical Section
				printf("\n\nIN CONSUMER....",pos);
				printf("\nConsumer consumes a value %d from the buffer",buffer[count-1]);
				buffer[count-1] = NULL;
				count--;
				printf("\nValues in Buffer:");
				sleep(1);
				for(int i=0; i<n; i++) {
					printf("%d\t",buffer[i]);
				}
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}