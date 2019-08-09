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
	while(1) {
		int sleepTime = rand()%7;
		sleep(sleepTime);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
				//Critical Section	
				printf("\n\nIN PRODUCER....%d",pos);
				int producerVal = rand()%222;
				printf("\nProducer generated a value: %d",producerVal);
				buffer[count] = producerVal;
				count++;
				sleep(1);
				printf("\n\nValues in Buffer: ");
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
	while(1) {
		int sleepTime = rand()%7;
		sleep(sleepTime);
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
				//Critical Section
				printf("\n\nIN CONSUMER....%d",pos);
				printf("\nConsumer consumes a value %d from the buffer",buffer[count-1]);
				buffer[count-1] = 0;
				count--;
				printf("\n\nValues in Buffer: ");
				sleep(1);
				for(int i=0; i<n; i++) {
					printf("%d\t",buffer[i]);
				}
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

void main() {
	int prod,cons,init,*b;
	pthread_t *thread1, *thread2;
	int pShared;						//Whether semaphore is shared btwn the threads i.e = 0
													//or shared btwn the processes i.e != 0	
	printf("\nNumber of producers:");
	scanf("%d",&prod);
	printf("\nNumber of consumers:");
	scanf("%d",&cons);
	printf("\nSize of Bounded Buffer:");
	scanf("%d",&n);

	buffer = (int *) calloc((n+1), sizeof(int));		//Allocates memory to buffer & initialises it to 0
	init = pthread_mutex_init(&mutex,NULL);				//Mutex Initialization
	if(init != 0) {
		printf("\nMutex Initialization failed!");
		exit(EXIT_FAILURE);
	}
	
	init = sem_init(&full,0,0);				//Semaphore Initialization
	if(init != 0) {
		printf("\nSemaphore Initialization failed!");
		exit(EXIT_FAILURE);
	}

	init = sem_init(&empty,0,n);			//Semaphore Initialization
	if(init != 0) {
		printf("\nSemaphore Initialization failed!");
		exit(EXIT_FAILURE);
	}
	thread1 = (pthread_t *) malloc(prod * sizeof(pthread_t));		//Allocates 'prod' threads
	thread2 = (pthread_t *) malloc(cons * sizeof(pthread_t));		//Allocates 'cons' threads
	printf("\n------------Creating Threads------------\n");
	for(int i=0; i<prod; i++) {
		b = &i;								//Which producer is producing
		init = pthread_create((thread1+i),NULL,producer,b);
		if(init != 0) {
			printf("\nThread Creation failed!");
			exit(EXIT_FAILURE);
		}
	}

	for(int i=0; i<cons; i++) {
		b = &i;								//Which consumer is consuming
		init = pthread_create((thread2+i),NULL,consumer,b);
		if(init != 0) {
			printf("\nThread Creation failed!");
			exit(EXIT_FAILURE);
		}
	}

	printf("\n------------Joining Threads------------\n");
	for(int i=0; i<prod; i++) {
		init = pthread_join(*(thread1+i),NULL);
		if(init != 0) {
			printf("\nThread Joining failed!");
			exit(EXIT_FAILURE);
		}
	}

	for(int i=0; i<cons; i++) {
		init = pthread_join(*(thread2+i),NULL);
		if(init != 0) {
			printf("\nThread Joining failed!");
			exit(EXIT_FAILURE);
		}
	}

	sem_destroy(&empty);
	sem_destroy(&full);
}