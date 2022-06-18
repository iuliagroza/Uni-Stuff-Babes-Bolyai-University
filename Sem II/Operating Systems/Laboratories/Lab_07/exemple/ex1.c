/*
	ex1.c
	Using exit status to send data from child to parent.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	int a = 3;
	int b = 7;

	int pid = fork();
	if (pid == -1)								// fork() failed
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)								// in child process
	{
		int sum = a + b;
		printf("[CHILD] Sum is %d\n", sum);

		exit(sum);								// send sum as exit status
	}
	else										// in parent process
	{
		// wait for child to finish
		int status;
		wait(&status);
		printf("[PARENT] Child PID %d has finished with exit status %d\n", pid, status);

		// get the sum from exit status
		int sum = WEXITSTATUS(status);
		printf("[PARENT] Sum returned by child is %d\n", sum);
	}

	return 0;
}
