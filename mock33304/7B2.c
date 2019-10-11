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
	int f1 = 0, f2 = 0, i = 0, ret;
	char readSentence[100], buffer[300];
	int numChar = 0, numWords = 0, numLines = 0, numLetters = 0;
	FILE *fp;

	ret = mkfifo("/home/oslab-22/Desktop/myFifo",0666);
	if ((ret < 0) && (errno != EEXIST)){
		printf("\nERROR IN CREATING THE FIFO...");
		exit(0);
	}

	if(errno == EEXIST) {
		printf("\nFIFO ALREADY EXISTS!\n");
	}

	printf("\nWAITING FOR OUTPUT FROM FIFO 1...\n");
	sleep(5);

	f1 = open("/home/oslab-22/Desktop/myFifo",O_RDONLY);
	read(f1,readSentence,100);

	int w = 0;
	for(i = 0; readSentence[i] != '\0'; i++) {
		if((readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?')) {
			numLines++;
		}
		
		if((readSentence[i] == ' ') || (readSentence[i] == ',')) {
			numWords++;
		}

		if((readSentence[i] == ' ') || (readSentence[i] == ',') || (readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?')) {
			w++;
		}
	}
	numChar = i-1;
	numLetters = i-w-1;

	fp = fopen("7B.txt","w");
	fprintf(fp, "\nNO. OF CHARACTERS = %d\n",numChar);
	fprintf(fp, "NO. OF LETTERS = %d\n",numLetters);
	fprintf(fp, "NO. OF WORDS = %d\n",numWords+1);
	fprintf(fp, "NO. OF LINES = %d\n",numLines);
	fprintf(fp,"%c",EOF);
	fclose(fp);

	fp = fopen("7B.txt","r");
	i = 0;
	while(fscanf(fp,"%c",&buffer[i++]) != EOF) {
		buffer[i] = '\0';
	}
	fclose(fp);

	printf("\nWRITING THE OUTPUT TO FIFO 1...\n");
	f2 = open("/home/oslab-22/Desktop/myFifo",O_WRONLY);
	write(f2,buffer,(strlen(buffer)+1));
	sleep(5);
	unlink("/home/oslab-22/Desktop/myFifo");
	return 0;
}