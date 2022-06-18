/*
	ex2.c
	A file opened by the parent process is inherited by the child process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX 50

int main(int argc, char* argv[])
{
	// open a file
	int fd = open("out.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)							// open() has failed
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if (pid == -1)						// fork() has failed
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)						// in child process
	{
		char msg[MAX+1];
		snprintf(msg, MAX, "[CHILD] My PID is %d Parent PID is %d\n", getpid(), getppid());
		write(fd, msg, strlen(msg));	// write to file

		exit(EXIT_SUCCESS);
	}
	else								// in parent process
	{
		// wait for child to finish
		int status;
		wait(&status);

		char msg[MAX+1];
		snprintf(msg, MAX, "[PARENT] My PID is %d Child PID is %d\n", getpid(), pid);
		write(fd, msg, strlen(msg));	// write to file
	}

	// close the file
	close(fd);

	return 0;
}
