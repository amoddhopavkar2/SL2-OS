#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (phil+4)%N
#define RIGHT (phil+1)%N

sem_t mutex;
sem_t S[5];

void philosopher(int *);
void pickup(int);
void putdown(int);
void test(int);

int state[N];
int phil[N] = {0,1,2,3,4};

int main()
{
	int i;
	pthread_t thread_ID[N];
	sem_init(&mutex,0,1);
	for(i=0; i<N; i++)
		sem_init(&S[i],0,0);
	
	for(i=0; i<N; i++) {
		pthread_create(&thread_ID[i],NULL,philosopher,&phil[i]);
		printf("\nPHILOSOPHER %d IS THINKING!",i+1);
	}

	for(i=0; i<N; i++)
		pthread_join(thread_ID[i],NULL);
}

void test(int phil)
{
	if(state[phil] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[phil] = EATING;
		sleep(2);
		printf("\nPHILOSOPHER %d TAKES CHOPSTICK %d and %d",phil+1,LEFT+1,phil+1);
		printf("\nPHILOSOPHER %d IS EATING!",phil+1);
		sem_post(&S[phil]);
	}
}

void *philosopher(void *num)
{
	while(1) {
		int *i = num;
		sleep(1);
		pickup(*i);
		sleep(0);
		putdown(*i);
	}
}

void pickup(int phil)
{
	sem_wait(&mutex);
	state[phil] = HUNGRY;
	printf("\nPHILOSOPHER %d IS HUNGRY!",phil+1);
	test(phil);
	sem_post(&mutex);
	sem_wait(&S[phil]);
	sleep(1);
}

void putdown(int phil)
{
	sem_wait(&mutex);
	state[phil] = THINKING;
	printf("\nPHILOSOPHER %d IS PUTTING DOWN THE CHOPSTICKS",phil+1);
	printf("\nCHOPSTICKS %d and %d PUT DOWN!",LEFT+1,phil+1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
}