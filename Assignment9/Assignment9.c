#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void create(char fileName[]) {
	int exists = access(fileName,F_OK);
	if(exists == 0) {
		printf("\nFILE ALREADY EXISTS!\n");
	}
	else {
		int fd = open(fileName,O_CREAT);
		if(fd < 0) {
			printf("\nERROR IN CREATING THE FILE!\n");
		}
		else {
			printf("\nFILE SUCCESSFULLY CREATED!\n");
		}
		close(fd);
	}
}

void readFile(char fileName[]) {
	char buffer[100];
	int content;
	int fd = open(fileName,O_RDONLY);
	if(fd < 0) {
		printf("\nERROR IN READING FROM THE FILE!\n");
	}
	else {
		while((content = read(fd,buffer,sizeof(buffer))) > 0) {
			printf("\nTHE CONTENTS OF THE FILE ARE: %s\n");
		}
		close(fd);
	}
}

void writeFile(char fileName[]) {
	char buffer[100];
	int sentence, i = 0;
	int fd = open(fileName,O_WRONLY|O_APPEND);
	if(fd < 0) {
		printf("\nERROR IN WRITING TO THE FILE!\n");
	}
	else {
		printf("\nENTER THE SENTENCE: ");
		do {
			scanf("%c",&buffer[i]);
			i++;
		} while(buffer[i] != '#');
		buffer[i-1] = '\0';
		//while(buffer[i] != '\0')
			//i++;
		//buffer[i] = '\0';
		write(fd,buffer,i-1);
		close(fd);
	}
}

int main() {
	int ch;
	char fileName[20];
	do {
		printf("\n1. CREATE A FILE: \n2. WRITE TO THE FILE: \n3. READ FROM THE FILE: \n4. EXIT. \n\nENTER YOUR CHOICE:");
		scanf("%d",&ch);
		switch(ch) {
			case 1:
				printf("\nENTER THE FILE NAME:");
				scanf("%s",fileName);
				create(fileName);
				break;

			case 2:
				writeFile(fileName);
				break;

			case 3:
				readFile(fileName);
				break;

			case 4:
				printf("\nEXITING THE PROGRAM...\n");
				return(0);
		}
	} while(ch != 4);
	return 0;
} 