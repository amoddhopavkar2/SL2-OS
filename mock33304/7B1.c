#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
extern int errno;

int main() {
	int f1 = 0, f2 = 0, ret = 0;
	char sentence[100], readSentence[100];
	printf("\nCREATING FIFO 1...\n");

	ret = mkfifo("/home/oslab-22/Desktop/myFifo",0666);
	if ((ret < 0) && (errno != EEXIST)){
		printf("\nERROR IN CREATING THE FIFO...");
		exit(0);
	}

	if(errno == EEXIST) {
		printf("\nFIFO ALREADY EXISTS!\n");
	}

	printf("\nENTER A SENTENCE: ");
	fgets(sentence,100,stdin);
	printf("\nWRITING THE SENTENCE TO FIFO 1...");

	f1 = open("/home/oslab-22/Desktop/myFifo",O_WRONLY);
	write(f1,sentence,(strlen(sentence)+1));
	printf("\nWAITING FOR OUTPUT FROM FIFO 2...");
	sleep(5);
	
	f2 = open("/home/oslab-22/Desktop/myFifo",O_RDONLY);
	read(f2,readSentence,300);
	printf("\nTHE OUTPUT IS: \n%s",readSentence);
	
	unlink("/home/oslab-22/Desktop/myFifo");
	return 0;
}