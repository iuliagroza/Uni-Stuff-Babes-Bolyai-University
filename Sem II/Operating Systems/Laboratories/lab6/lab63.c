#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char**argv) {
	if(argc > 1) {
		int pidA = atoi(argv[1]);

		while(1) {
			printf("Sending HUP to %d\n", pidA);
			kill(pidA, SIGHUP);
			sleep(5);
		}
	} else {
		perror("Usage: pid of a process missing");
		exit(1);
	}
}
