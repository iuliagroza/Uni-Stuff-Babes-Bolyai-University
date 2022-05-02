#include <stdio.h>

int main() {
	int p = fork();
	if (p<0) {
		perror("Unable to create child process");
		exit(1);
	}
	if(p==0) {
		//child process
		printf("Child pid: %d parent pid: %d\n", getpid(), getppid());
		//heavy cpu
		int i=0;
		while(i<10) {
			printf("Enter number: ");
			scanf("%d", &n);
		}
		kill(getppid(), SIGUSR1);
		exit(0);
	}
	srand(getpid());
	int s = rand()%10+5;
	printf("Will wait up to %d seconds\n", s);
	sleep(s);
	printf("Sending kill signal");
	kill(p, SIGTERM);
	return 0;
}
