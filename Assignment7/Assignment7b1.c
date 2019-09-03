#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main() {
	int f1 = 0,f2 = 0,ret = 0;
	char sentence[100],readSentence[300];
	printf("\nCREATING NAMED-PIPE 1...");
	
	ret = mkfifo("/tmp/Fifo1",0666);
	if((ret < 0) && (errno != EEXIST)) {
		printf("\nERROR WHILE CREATING THE FIFO\n");
		return;
	}

	if(errno == EEXIST) {
		printf("\nFIFO ALREADY EXISTS!\n");
	}

	printf("\nENTER A SENTENCE: ");
	fgets(sentence,100,stdin);
	printf("\n\nWRITING THE SENTENCE TO FIFO 1...");
	printf("\nWRITING THE SENTENCE TO FIFO 1...");
	
	f1 = open("/tmp/Fifo1",O_WRONLY);
	write(f1,sentence,(strlen(sentence)+1));
	printf("\nWAITING FOR OUTPUT FROM FIFO 2...");
	sleep(5);
	
	f2 = open("/tmp/Fifo2",O_RDONLY);
	read(f2,readSentence,300);
	printf("\nTHE OUTPUT IS: %s",readSentence);
	
	unlink("/tmp/Fifo1");
	return 0;
}