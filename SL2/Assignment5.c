#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define max 10

int readCount = 0, val = 0;
pthread_mutex_t mutex;
sem_t writer;

void *readers(void *arg) {
	int pos = *(int *)arg;
	while(1) {
		pthread_mutex_lock(&mutex);
			readCount++;
			if (readCount == 1) {
				sem_wait(&writer);
			}
		pthread_mutex_unlock(&mutex);
		printf("\nREADER '%d' READS VALUE %d...",pos,val);

		pthread_mutex_lock(&mutex);
			readCount--;
			if (readCount == 0) {
				sem_post(&writer);
			}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *writers(void *arg) {
	int pos = *(int *)arg;
	while(1) {
		sem_wait(&writer);
			val += rand()%7;
			printf("\n\nWRITER '%d' WRITES VALUE %d...",pos,val);
		sem_post(&writer);
		sleep(1);
	}
}

int main() {
	int reads,writes,init,*num;
	pthread_t read[max], write[max];

	printf("\nNO OF READERS: ");
	scanf("%d",&reads);
	printf("\nNO OF WRITERS: ");
	scanf("%d",&writes);

	init = pthread_mutex_init(&mutex,NULL);
	if (init != 0) {
		printf("\nMUTEX INITIALIZATION FAILED...");
		exit(1);
	}

	init = sem_init(&writer,0,1);
	if (init != 0) {
		printf("\nSEMAPHORE INITIALIZATION FAILED...");
		exit(1);
	}

	for (int i=0; i<writes; i++) {
		num = &i;
		if (pthread_create(&write[i],NULL,writers,num) != 0) {
			printf("\nTHREAD CREATION FAILED...");
			exit(1);
		}

		else {
			printf("\n\nWRITER THREAD NO '%d' CREATED...",i+1);
		}
	}

	for (int i=0; i<reads; i++) {
		num = &i;
		if (pthread_create(&read[i],NULL,readers,num) != 0) {
			printf("\nTHREAD CREATION FAILED...");
			exit(1);
		}

		else {
			printf("\n\nREADER THREAD NO '%d' CREATED...",i+1);
		}
	}

	for (int i=0; i<reads; i++) {
		if (pthread_join(read[i],NULL) != 0) {
			printf("\nREADER THREAD JOINING FAILED...");
		}
	}

	for (int i=0; i<writes; i++) {
		if (pthread_join(write[i],NULL) != 0) {
			printf("\nWRITER THREAD JOINING FAILED...");
		}
	}
}
