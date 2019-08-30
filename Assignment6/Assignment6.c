#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (phNum+N-1)%N
#define RIGHT (phNum+1)%N
sem_t mutex;
sem_t S[N];

int state[N];
int phil[N] = {0,1,2,3,4};
int eating[N] = {0};

void display()
{
	int i;
	printf("\n\n---------------------------------------------------");
	printf("\nPHILOSOPHER NO:\t  ");
	for(i=0; i<N; i++)
		printf("%d\t",i+1);
	printf("\n---------------------------------------------------");
	printf("\nNO OF TIMES EATEN:");
	for(i=0; i<N; i++)
		printf("%d\t",eating[i]);
	printf("\n---------------------------------------------------");
	printf("\n\n");
}

void test(int phNum)
{
	if(state[phNum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
		state[phNum] = EATING;
		eating[phNum]++;
		sleep(2);
		printf("\n\nPHILOSOPHER %d TAKES CHOPSTICK %d and %d",phNum+1,LEFT+1,phNum+1);
		printf("\nPHILOSOPHER %d IS EATING!",phNum+1);
		display();
		sem_post(&S[phNum]);
	}
}

void pickup(int phNum)
{
	sem_wait(&mutex);
	state[phNum] = HUNGRY;
	printf("\n\nPHILOSOPHER %d IS HUNGRY!",phNum+1);
	test(phNum);
	sem_post(&mutex);
	sem_wait(&S[phNum]);
	sleep(1);
}

void putdown(int phNum)
{
	sem_wait(&mutex);
	state[phNum] = THINKING;
	printf("\n\nPHILOSOPHER %d IS PUTTING DOWN THE CHOPSTICKS",phNum+1);
	printf("\nCHOPSTICKS %d and %d ARE PUT DOWN!",LEFT+1,phNum+1);
	printf("\nPHILOSOPHER %d IS THINKING!",phNum+1);
	test(LEFT);
	test(RIGHT);
	sem_post(&mutex);
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

int main()
{
	int i;
	pthread_t thread_ID[N];
	sem_init(&mutex,0,1);
	for(i=0; i<N; i++)
		sem_init(&S[i],0,0);
	
	for(i=0; i<N; i++) {
		pthread_create(&thread_ID[i],NULL,philosopher,&phil[i]);
		printf("\n\nPHILOSOPHER %d IS THINKING!",i+1);
	}

	for(i=0; i<N; i++)
		pthread_join(thread_ID[i],NULL);
}