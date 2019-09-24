#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct student {
	int roll;
	char name[20];
	float marks;
	int class;
}Student;

void createData(char dataName[]) {
	int exists = access(dataName,F_OK);
	if(exists == 0) 
		printf("\nDatabase already exists!\n");
	else {
		int fd = open(dataName,O_CREAT);
		if(fd < 0) {
			printf("\nError in creating the database!");
			exit(0);
		}
		else
			printf("\nDatabase created successfully!");
		close(fd);
	}
}

void writeData(char dataName[]) {
	Student s;
	printf("\nEnter Roll no:");
	scanf("%d",&s.roll);
	printf("\nEnter Name:");
	scanf("%s",s.name);
	printf("\nEnter Marks:");
	scanf("%f",&s.marks);
	printf("\nEnter Class:");
	scanf("%d",&s.class);
	
	int fd = open(dataName,O_WRONLY | O_APPEND);
	if(fd < 0){
		printf("\nError in writing the record!\n");
		exit(0);
	}
	else {
		write(fd,&s,sizeof(s));
		printf("\nRecord written successfully!\n");
	}
	close(fd);
}

void readData(char dataName[]) {
	Student s;
	int fd = open(dataName,O_RDONLY);
	if(fd < 0) {
		printf("\nError in reading the database!");
		exit(0);
	}
	else {
		printf("\nRoll No \tName \tMarks \tClass\n");
		while(read(fd,&s,sizeof(s)))
			printf("%d \t%s \t%f \t%d",s.roll,s.name,s.marks,s.class);
	}
	close(fd);
}

int main() {
	int ch;
	Student s;
	char dataName[20];
	while(1) {
		printf("\n\n---STUDENTS DATABASE IN FILES---\n");
		printf("\n1. Create database: \n2. Insert records: \n3. Display records: \n4. Search: \n5. Modify: \n6. Delete: \n7. Exit\n\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch) {
			case 1:
				printf("\nEnter database name:");
				scanf("%s",dataName);
				createData(dataName);
				break;

			case 2:
				writeData(dataName);
				break;

			case 3:
				readData(dataName);
				break;

			case 4:
			break;

			case 5:
			break;

			case 6:
			break;

			case 7:
			return 0;

			default:
			printf("\n\nEnter a choice between 1 to 7!");
		}
	}
}