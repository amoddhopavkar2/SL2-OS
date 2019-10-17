#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define N 5
#define LEFT (philNum+N-1)%N
#define RIGHT (philNum+1)%N

sem_t mutex, S[N];
int eating[N] = {0}, state[N];
int phil[N] = {0,1,2,3,4,};

void display() {
	printf("\n\nPHILOSOPHER NO: \t ");
	for (int i=0; i<N; i++) {
		printf("%d\t",i);
	}
	printf("\n============================================================");
	printf("\nNO OF TIMES EATEN: \t");
	for (int i=0; i<N; i++) {
		printf("%d\t",eating[i]);
	}
	printf("\n=============================================================");
}

void test(int philNum) {
	if (state[philNum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[philNum] = EATING;
		eating[philNum]++;
		sleep(2);
		printf("\n\nPHILOSOPHER '%d' IS EATING...",philNum);
		printf("\nPHILOSOPHER '%d' PICKS UP CHOPSTICKS '%d' & '%d'...",philNum,LEFT,RIGHT);
		display();
		sem_post(&S[philNum]);
	}
}

void pickup(int philNum) {
	sem_wait(&mutex);
	state[philNum] = HUNGRY;
	printf("\n\nPHILOSOPHER '%d' IS HUNGRY...",philNum);
	test(philNum);
	sem_post(&mutex);
	sem_wait(&S[philNum]);
	sleep(1);
}

void putdown(int philNum) {
	sem_wait(&mutex);
	state[philNum] = THINKING;
	printf("\n\nPHILOSOPHER '%d' PUTS DOWN CHOPSTICKS '%d' & '%d'...",philNum,LEFT,RIGHT);
	printf("\nPHILOSOPHER '%d' IS THINKING...",philNum);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}

void *philosopher(void *arg) {
	while(1) {
		int *num = arg;
		sleep(1);
		pickup(*num);
		sleep(1);
		putdown(*num);
	}	
}

int main() {
	int init;
	pthread_t threads[N];
	init = sem_init(&mutex,0,1);
	if (init != 0) {
		printf("\nSEMAPHORE INITIALIZATION FAILED....");
		exit(1);
	}

	for (int i=0; i<N; i++) {
		init = sem_init(&S[i],0,0);
		if (init != 0) {
			printf("\nSEMAPHORE INITIALIZATION FAILED...");
			exit(1);
		}
	}

	for (int i=0; i<N; i++) {
		pthread_create(&threads[i],NULL,philosopher,&phil[i]);
		printf("\n\nPHILOSOPHER '%d' IS THINKING...",i);
	}

	for (int i=0; i<N; i++) {
		pthread_join(threads[i],NULL);
	}

	return 0;
}