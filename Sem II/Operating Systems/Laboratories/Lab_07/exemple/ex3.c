/*
	ex2.c
	Using a file to send data from child to parent.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 5


int main(int argc, char* argv[])
{
	// open the file
	int fd = open("out.bin", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0 )
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}

	int i, pid[MAX];
	int pv[MAX] = {1, 2, 3, 4, 5};
	for (i = 0; i < MAX; i++)
	{
		int j = i;

		pid[i] = fork();					// try to create a child process
		if (pid[i] == -1)					// fork() has failed
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid[i] == 0)					// in child process
		{
			int val = pv[j]*pv[j];			// compute the square of pv[j]
			write(fd, &val, sizeof(int));	// write it to the file

			printf("[CHILD] PID %d has written the value %d.\n", getpid(), val);

			exit(EXIT_SUCCESS);
		}
	}

	// in parent process
	int status;
	for(i = 0; i < MAX; i++)
	{
		wait(&status);
		printf("[PARENT] Child with PID %d has finished with exit status %d.\n", pid[i], status);
	}

	// move to the beggining of file
	lseek(fd, SEEK_SET, 0);

	int cv[MAX];
	for(i = 0; i < MAX; i++)
	{
		read(fd, &cv[i], sizeof(int));
		printf("[PARENT] cv[%d]: %d\n", i, cv[i]);
	}

	// close the file
	close(fd);

	return 0;
}
