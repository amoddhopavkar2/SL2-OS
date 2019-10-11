#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX 100

int main() {
	int fd1[2], fd2[2], nbytes = 1, a = 0;
	pid_t pid;
	char file[MAX], readBuffer[MAX], ch = 'a', ch1 = '\n';
	FILE *fp;

	pipe(fd1);
	pipe(fd2);

	if ((pid = fork()) < 0) {
		printf("\nERROR IN FORKING...");
		exit(0);
	}

	if (pid == 0) {
		sleep(5);
		printf("\nIN CHILD PROCESS...\n");
		close(fd1[1]);
		read(fd1[0],readBuffer,sizeof(readBuffer));
		printf("\nFILE '%s' IS READ BY CHILD PROCESS THROUGH PIPE 1...",readBuffer);
		fp = fopen(readBuffer,"r");
		close(fd1[0]);
		close(fd2[0]);
		printf("\nCONTENTS OF THE FILE ARE SENT TO PARENT BY THE CHILD PROCESS THROUGH PIPE 2...");
		while (a != -1) {
			a = fscanf(fp,"%c",&ch);
			write(fd2[1],&ch,sizeof(ch));
		}
		close(fd2[1]);
		exit(0);
	}

	else {
		close(fd1[0]);
		printf("\nIN PARENT PROCESS...\n");
		printf("\nENTER THE FILE NAME: ");
		scanf("%s",file);
		printf("\nFILENAME IS SENT BY PARENT TO CHILD PROCESS THROUGH PIPE 1...");
		write(fd1[1],file,(strlen(file)+1));
		close(fd1[1]);
		close(fd2[1]);
		sleep(5);

		printf("\nIN PARENT PROCESS...\n");
		printf("\nCONTENTS OF '%s' ARE RECEIVED BY THE PARENT THROUGH PIPE 2...",file);
		printf("\nTHE RECEIVED MESSAGE IS: ");
		while (nbytes != 0) {
			printf("%c",ch1);
			nbytes = read(fd2[0],&ch1,sizeof(ch1));
		}
		close(fd2[0]);
	}
	return 0;
}