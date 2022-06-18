/*
	ex4.c
	Using signal() to set actions that will occur when a signal is delivered to the process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX 50

volatile sig_atomic_t stop = 1;

// define the signal handler
void sig_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		char msg[MAX+1];
		snprintf(msg, MAX, "Process PID %d has received SIGUSR1 signal.\n", getpid());

		// printf() is not async-signal-safe function
		write(STDOUT_FILENO, msg, strlen(msg));
		
		stop = 0;
	}
}


int main(int argc, char* argv[])
{
	signal(SIGUSR1, sig_handler);	// set the signal disposition

	int pid = fork();
	if (pid == -1)					// fork() has failed
	{
		perror("fork() error: ");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)					// in child process
	{
		printf("[CHILD] My PID is %d Parent PID is %d\n", getpid(), getppid());

		while(stop)
		{
			sleep(2);
		}

		printf("[CHILD] I finished my job\n");

		exit(EXIT_SUCCESS);
	}
	else							// in parent process
	{
		printf("[PARENT] My PID is %d Child PID is %d\n", getpid(), pid);

		int status;
		wait(&status);
		printf("[PARENT] Child PID %d has finished with exit status %d\n", pid, status);
	}

	return 0;
}
