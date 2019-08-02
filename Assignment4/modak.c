#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>


sem_t full,empty;		//declaring semaphore
pthread_mutex_t m;		//declaration of mutex
int n;
int count=0;
int *buffer;


void * producer(void *args){		//will pass number of arguments
	int i;
	int pos = *(int *)args;
	while(1){
		sleep(rand()%7);
		sem_wait(&empty);
		pthread_mutex_lock(&m);
		//critical section
				printf("\nIN PRODUCER...%d\n",pos);
				buffer[count] = rand()%222;
				printf("\nPRODUCER GENERATED VALUE : %d\n",buffer[count]);
				count++;
				sleep(1);
				printf("\nBUFFER IS : \n{");
				for(i=0;i<n;i++){
					printf(" %d ",buffer[i]);
				}
				printf(" }\n");
		pthread_mutex_unlock(&m);
		sem_post(&full);
	}	
	pthread_exit(NULL);
}

void * consumer(void *args){		//will pass number of arguments
	int i;
	int pos = *(int *)args;
	while(1){
		sleep(rand()%7);
		sem_wait(&full);
		pthread_mutex_lock(&m);
		//critical section
				printf("\nIN CONSUMER...%d\n",pos);
				printf("\nCONSUMER CONSUMED : %d",buffer[count-1]);
				buffer[count-1] = 0;
				count--;
				printf("\nBUFFER IS : \n{");
				sleep(1);
				for(i=0;i<n;i++){
					printf(" %d ",buffer[i]);
				}
				printf(" }\n");
		pthread_mutex_unlock(&m);
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

void main(){
	int *b,err,p,c,i;
	pthread_t *thread1,*thread2;		//declaration of thread
	int pshared;						//wheather semaphore is shared between the threads i.e = 0
										//or shared between the processes i.e != 0

	printf("HOW MANY PRODUCERS ?\n");
	scanf("%d",&p);
	printf("HOW MANY CONSUMERS ?\n");
	scanf("%d",&c);
	printf("Enter the size of BOUNDED BUFFER\n");
	scanf("%d",&n);						//size of buffer

	//allocating memory to buffer
	buffer = (int *) calloc((n+1),sizeof(int));		//to initialize it directly to zero
	
	err = pthread_mutex_init(&m,NULL);			//mutex initialization
	if(err!=0){
		printf("MUTEX INITIALIZATION FAILED\n");
		exit(EXIT_FAILURE);
	}
	err = sem_init(&full,0,0);				//semaphore initialization
	if(err !=0){
		printf("SEMAPHORE INITIALIZATION FAILED...\n");
		exit(EXIT_FAILURE);
	}
	err  = sem_init(&empty,0,n);			//semaphore initialization
    if(err !=0){
		printf("SEMAPHORE INITIALIZATION FAILED...\n");
		exit(EXIT_FAILURE);
	}
	thread1 = (pthread_t *) malloc(p*sizeof(pthread_t));		//allocating p threads
	thread2 = (pthread_t *) malloc(c*sizeof(pthread_t));		//allocating c threads
	
	printf("\n:::::::::::::::::::::CREATING THREADS:::::::::::::::::::\n");

	for(i=0;i<p;i++){											//producer thread creation
			b = &i;//to know which producer is producing
			err = pthread_create((thread1+i),NULL,producer,b);
			if(err!=0){
				printf("THREAD CREATION FAILED...\n");
				exit(EXIT_FAILURE);
			}
	}
	
	for(i=0;i<c;i++){			//consumer thread creation
			b = &i;	//to know which consumer is consuming
			err = pthread_create((thread2+i),NULL,consumer,b);
			if(err!=0){
				printf("THREAD CREATION FAILED...\n");
				exit(EXIT_FAILURE);
			}
	}

	printf("\n:::::::::::::::::JOINGING THREADS ::::::::::::\n");

	for(i=0;i<p;i++){
		err = pthread_join(*(thread1+i), NULL);	
			// check for thread join failure
			if (err != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}
	}

	for(i=0;i<c;i++){
		err = pthread_join(*(thread2+i), NULL);	
			// check for thread join failure
			if (err != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}
	}
	sem_destroy(&full);
	sem_destroy(&empty);
	printf("PROGRAM FINISHED...\n");
	
}