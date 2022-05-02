#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int p[2];
	if(pipe(p)<0) {
		perror("Unable to create pipe channel.");
		exit(1);
	}
	
	int f = fork();
	if(f < 0) {
		perror("Unable to create a child process.");
		exit(2);
	}

	if(f == 0) {
		//child process
		//send an integer value to the parent
		close(p[0]); //close the raeding end
		char *b=(char*)malloc(sizeof(char)*21);
		printf("Enter word: ");
		scanf("%20s", b);
		srand(getpid());
		int n=strlen(b);
		printf("[%d]We are sending: %d\n", getpid(), n);
		if(write(p[1], &n, sizeof(int)) < 0) {
			perror("Unable to send.");
			exit(3);
		}
		printf("[%d]We are sending: %s\n", getpid(), b);
		if(write(p[1], &b, sizeof(char)*n) < 0) {
			perror("Unable to send.");
			exit(3);
		}
		close(p[1]);
		free(b);
		exit(0);
	}

	//executed only by the parent process
	
	//close the unused end
	close(p[1]);
	int r;
	printf("[%d]Before read\n:", getpid());
	if(read(p[0], &r, sizeof(int)) < 0) {
		perror("Unable to read.");
		exit(4);
	}
	char *buff = (char*)malloc(r*sizeof(char)+1);
	printf("[%d]We received: %d\n", getpid(), r);
	printf("[%d]Before second read\n:", getpid());
	int rb = 0;
	if((rb = read(p[0], buff, sizeof(int))) < 0) {         
		perror("Unable to read.");           	
		exit(4);                              
	}                                             
	buff[rb] = 0;
	printf("[%d]We received: %d\n", getpid(), r);

	close(p[0]);
	free(buff);
	return 0;
}
