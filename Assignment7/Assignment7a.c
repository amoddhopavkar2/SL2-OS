#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX 100

int main() {
	int fd1[2],fd2[2],nbytes = 1,a = 0;
	pid_t pid;
	char file[MAX],readBuffer[MAX];
	char ch = 'a',ch1 = '\n';
	FILE *fp;

	pipe(fd1);
	pipe(fd2);

	if((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if(pid == 0) {
		sleep(5);
		close(fd1[1]);
		read(fd1[0],readBuffer,sizeof(readBuffer));
		printf("\nFILE '%s' IS BEING READ BY CHILD PROCESS THROUGH PIPE 1...\n",readBuffer);
		fp = fopen(readBuffer,"r");
		close(fd1[0]);
		close(fd2[0]);
		printf("\nCONTENTS OF '%s' ARE BEING SENT TO PARENT PROCESS THROUGH PIPE 2...\n",readBuffer);
		while(a != -1) {
			a = fscanf(fp,"%c",&ch);
			write(fd2[1],&ch,sizeof(ch));
		}
		close(fd2[1]);
		exit(0);
	}

	else {
		close(fd1[0]);
		printf("\nIN PARENT PROCESS\n");
		printf("\nENTER THE FILENAME: ");
		scanf("%s",file);
		printf("\nFILENAME IS BEING SENT BY PARENT PROCESS TO CHILD PROCESS THROUGH PIPE 1...");
		write(fd1[1],file,(strlen(file)+1));
		close(fd1[1]);
		close(fd2[1]);
		sleep(5);

		printf("\nCONTENTS OF '%s' ARE RECEIVED BY THE PARENT PROCESS THROUGH PIPE 2...",file);
		printf("\nIN PARENT PROCESS\n");
		printf("\nRECEIVED MESSAGE IS: ");

		while(nbytes != 0) {
			printf("%c",ch1);
			nbytes = read(fd2[0],&ch1,sizeof(ch1));
		}
		close(fd2[0]);
	}
	return 0;
}
