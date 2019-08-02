#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
int shared_inventory[10],empty =10,full =0,prod_limit = 0;

void *prod(void *args)
{
	if (full == 10)
	{
		printf("Producer cannot produce any items,waiting for consumer to consume\n\n\n");
		return (void *)-1;
	}
	while(pthread_mutex_lock(&mutex)!= 0);
	shared_inventory[full++] =1;
	prod_limit++;
	printf("Producer has produced an Item,Total Items present = %d\n\n\n",full );
	empty--; 
	pthread_mutex_unlock(&mutex);
	return (void *)0;

}

void * cons(void * args)
{
	if (full == 0)
	{
		printf("Consumer cannot consume any items,waiting for Producer to Produce\n\n\n");
		return (void *)-1;
	}
	while(pthread_mutex_lock(&mutex)!= 0);
	shared_inventory[full--] =0;
	printf("Consumer has taken an Item,Total Items present = %d\n\n\n",full );
	empty++;
	pthread_mutex_unlock(&mutex);
	return (void *)0;
}

void *produce(void *args)
{
	int count = 0;
	pthread_t *thread_id = malloc(sizeof(pthread_t) * *(int *)args);
	for (int i = 0; i < *(int *)args; ++i)
		thread_id[i] = -1;
	while(prod_limit <= 50)
	{
		if (count < *(int *)args)
		{
			for (int i = 0; i < *(int *)args; ++i){
				if (thread_id[i] == -1){
					pthread_create((thread_id +i),NULL,prod,NULL);
					count++;
					sleep(2);
				}
			}
		}
		for (int i = 0; i < *(int *)args; ++i){
			if (thread_id[i] != -1){
				pthread_join(*(thread_id +i),NULL);
				thread_id[i] = -1;
				count--;
			}
		}
	}
}

void *consume(void *args)
{
	int count = 0;
	pthread_t *thread_id = malloc(sizeof(pthread_t) * *(int *)args);
	for (int i = 0; i < *(int *)args; ++i)
		thread_id[i] = -1;
	while(prod_limit <= 50)
	{
		if (count < *(int *)args)
		{
			for (int i = 0; i < *(int *)args; ++i)
			{
				for (int i = 0; i < *(int *)args; ++i)
				{
					if (thread_id[i] == -1){
						pthread_create((thread_id +i),NULL,cons,NULL);
						count++;
						sleep(2);
					}
				}
			}
		}
		for (int i = 0; i < *(int *)args; ++i){
			if (thread_id[i] != -1){
				pthread_join(*(thread_id +i),NULL);
				thread_id[i] = -1;
				count--;
			}
		}
	}

}


void init(void ){
	for (int i = 0; i < 10; ++i)
		shared_inventory[i] = 0;
}

int main(int argc, char const *argv[])
{
	int p,c;
	printf("Enter Number of Producers:");
	scanf("%d",&p);
	printf("Enter Number of Consumers:");
	scanf("%d",&c);
	pthread_t c_id,p_id;
	init();
	pthread_create(&p_id,NULL,&produce,&p);
	pthread_create(&c_id,NULL,&consume,&c);
	pthread_join(p_id,NULL);
	pthread_join(c_id,NULL);
	return 0;
}