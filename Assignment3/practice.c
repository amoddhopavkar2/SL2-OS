#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int sum; 									/*This data is shared by the thread(s) */
void *runner(void *param)					/*The thread will begin control in this function */
{
	int upper = atoi(param);
	int i;
	sum=0;

	if(upper > 0)
	{
		for(i=1; i <= upper;i++)
		sum += i;
	}
	pthread_exit(0);
}

void main(int argc, char *argv[]) 
{
	pthread_t tid; 							/* the thread identifier */
	pthread_attr_t attr; 					/* set of thread attributes */

	if(argc != 2) 
	{
		fprintf(stderr,"usage: a.out <integer value>\n");
		exit(0);
	}

	if(atoi(argv[1]) < 0)
	{
		fprintf(stderr, "%d must be >= 0 \n", atoi(argv[1]));
		exit(0);
	}

	pthread_attr_init(&attr);						/* get the default attributes */
	pthread_create(&tid,&attr,runner,argv[1]);		/*create the thread */
	pthread_join(tid,NULL);							/* Now wait for the thread to exit */
	printf("sum = %d\n",sum);
}