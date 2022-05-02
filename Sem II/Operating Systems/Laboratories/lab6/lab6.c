#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int p = fork();
	if(p<0) {
		perror("Unable to create p2.");
		exit(1);
	}
	if(p==0) {
		char *cmd = malloc(20*sizeof(char));
		printf("Enter command: ");
		scanf("%s", cmd);
		int p3 = fork();
		if(p3<0) {
			perror("Unable to create p3.");
			exit(2);
		}
		if(p3==0) {
			printf("Trying to execute: %s\n", cmd);
			if(execl(cmd, cmd, NULL) < 0) {
				perror("Error in executing cmd.");
				exit(3);
			}
		}
		wait(0);
		exit(0);
	}
	wait(0);
	return 0;
}
																			         
