#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

int n, count=0, *buffer;
sem_t full,empty;
pthread_mutex_t m;

void *producer(void *args);
void *consumer(void *args);

int main()
{
	int p,c,n,i,value,*b;
	pthread_t *t1,*t2;

	printf("\nNUMBER OF PRODUCERS:");
	scanf("%d",&p);
	printf("\nNUMBER OF CONSUMERS:");
	scanf("%d",&c);
	printf("\nSIZE OF BOUNDED BUFFER:");
	scanf("%d",&n);
 
	buffer = (int *) calloc((n+1), sizeof(int));

	value = pthread_mutex_init(&m,NULL);
	if(value != 0) 
	{
		printf("\nMutex Initialization failed!\n");
		exit(-1);
	}

	value = sem_init(&full,0,0);
	if(value != 0)
	{
		printf("\nSemaphore Initialization failed!\n");
		exit(-1);
	}

	value = sem_init(&empty,0,n);
	if(value != 0)
	{
		printf("\nSemaphore Initialization failed!\n");
		exit(-1);
	}

	t1 = (pthread_t *) malloc(p * sizeof (pthread_t));
	t2 = (pthread_t *) malloc(c * sizeof (pthread_t));

	printf("\n------------ Creating Threads ------------\n");

	for(i=0; i<p; i++)
	{
		b = &i;
		value = pthread_create((t1+1),NULL,producer,b);
		if(value != 0)
		{
			printf("\nThread Creation failed!\n");
			exit(-1);
		}
	}

	for(i=0; i<c; i++)
	{
		b = &i;
		value = pthread_create((t2+1),NULL,consumer,b);
		if(value != 0)
		{
			printf("\nThread Creation failed!\n");
			exit(-1);
		}
	}

	printf("\n------------ Joining Threads ------------");

	for(i=0; i<p; i++)
	{
		value = pthread_join(*(t1+i),NULL);
		if(value != 0)
		{
			printf("\nThread Joining failed!\n");
			exit(-1);
		}
	}

	for(i=0; i<c; i++)
	{
		value = pthread_join(*(t2+1),NULL);
		if(value != 0)
		{
			printf("\nThread Joining failed!\n");
			exit(-1);
		}
	}
	sem_destroy(&full);
	sem_destroy(&empty);
}

void *producer(void *args)
{
	int i;
	int pos = *(int *)args;

	while(1)
	{
		int z = rand()%7 + 1;
		sleep(z);
		sem_wait(&empty);
		pthread_mutex_lock(&m);
			//Critical Section
			printf("\n\nIN PRODUCER %d.....,",pos);
			buffer[count] = rand()%222;
			printf("\n\nPRODUCER GENETRATED VALUE: %d",buffer[count]);
			count++;
			sleep(1);
			printf("\n\nBUFFER IS: { ");
			for(i=0; i<n; i++)
				printf("%d ",buffer[i]);
			printf(" }\n");
		pthread_mutex_unlock(&m);
		sem_post(&full);
	}
	pthread_exit(NULL);
}

void *consumer(void *args)
{
	int i;
	int pos = *(int *)args;
	while(1)
	{
		int z = rand()%7 +1;
		sleep(z);
		sem_wait(&full);
		pthread_mutex_lock(&m);
			//Critical Section
			printf("\n\nIN CONSUMER %d.....,",pos);
			printf("\nCONSUMER CONSUMED: %d",buffer[count-1]);
			buffer[count-1] = 0;
			count--;
			printf("\n\nBUFFER IS: { ");
			sleep(1);
			for(i=0; i<n; i++)
				printf("%d ",buffer[i]);
			printf(" }\n");
		pthread_mutex_unlock(&m);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

