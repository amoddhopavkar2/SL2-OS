#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int size, *buffer, count = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
	int pos = *(int *)arg;
	while(1) {
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
			printf("\n\nIN PRODUCER %d...",pos);
			int val = rand()%10;
			printf("\nPRODUCER GENERATED A VALUE %d...",val);
			buffer[count] = val;
			count++;
			sleep(2);
			printf("\n===========================================================");
			printf("\nVALUES IN BUFFER: ");
			for (int i=0; i<size; i++) {
				printf("%d\t",buffer[i]);
			}
			printf("\n===========================================================\n");
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	} 
	pthread_exit(NULL);
}

void *consumer(void *arg) {
	int pos = *(int *)arg;
	while(1) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
			printf("\n\nIN CONSUMER %d...",pos);
			printf("\nCONSUMER CONSUMES A VALUE %d FROM THE BUFFER",buffer[count-1]);
			buffer[count-1] = 0;
			count--;
			sleep(2);
			printf("\n===========================================================");
			printf("\nVALUES IN BUFFER: ");
			for (int i=0; i<size; i++) {
				printf("%d\t",buffer[i]);
			}
			printf("\n===========================================================\n");
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

int main() {
	int prod, cons, init, *num;
	pthread_t *thread1, *thread2;

	printf("\nNO OF PRODUCERS:");
	scanf("%d",&prod);
	printf("\nNO OF CONSUMERS:");
	scanf("%d",&cons);
	printf("\nSIZE OF BUFFER:");
	scanf("%d",&size);

	buffer = (int *)calloc((size+1), sizeof(int));
	init = pthread_mutex_init(&mutex,NULL);
	if (init != 0) {
		printf("\nMUTEX INITIALIZATION FAILED...");
		exit(1);
	}

	init = sem_init(&empty,0,size);
	if (init != 0) {
		printf("\nSEMAPHORE INITIALIZATION FAILED...");
		exit(1);
	}

	init = sem_init(&full,0,0);
	if (init != 0) {
		printf("\nSEMAPHORE INITIALIZATION FAILED...");
		exit(1);
	}

	thread1 = (pthread_t *)malloc(prod * sizeof(pthread_t));
	thread2 = (pthread_t *)malloc(cons * sizeof(pthread_t));

	for (int i=0; i<prod; i++) {
		num = &i;
		init = pthread_create(thread1+i,NULL,producer,num);
		if (init != 0) {
			printf("\nTHREAD CREATION FAILED...");
			exit(1);
		}
	}

	for (int i=0; i<cons; i++) {
		num = &i;
		init = pthread_create(thread2+i,NULL,consumer,num);
		if (init != 0) {
			printf("\nTHREAD CREATION FAILED...");
			exit(1);
		}
	}

	for (int i=0; i<prod; i++) {
		init = pthread_join(*(thread1+i),NULL);
		if (init != 0) {
			printf("\nTHREAD JOINING FAILED...");
			exit(1);
		}
	}

	for (int i=0; i<cons; i++) {
		init = pthread_join(*(thread2+i),NULL);
		if (init != 0) {
			printf("\nTHREAD JOINING FAILED...");
			exit(1);
		}
	}

	sem_destroy(&empty);
	sem_destroy(&full);
}