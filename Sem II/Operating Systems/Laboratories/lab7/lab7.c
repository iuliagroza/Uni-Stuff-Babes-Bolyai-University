#include <stdio.h>

int main() {
	int p1 = fork();
	if(p1<0) {
		perror("Unable to create child process p1.");
		exit(1);
	}
	if(p1 == 0) {
		//child process
		sleep(30);
		int r1 = kill(getppid(), SIGUSR1);
		printf("r2: %d", r2);
	}

	int p2 = fork();
	if(p2<0) {
		perror("Unable to create child process.");
	}
	if(p2 == 0) {
		int r2 = kill(getpid(), SIGUSR2);
		printf("r1: %d", r1);
	}
	return 0;
}
