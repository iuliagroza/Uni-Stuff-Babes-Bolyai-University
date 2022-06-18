//
// Using variables defined in parent process
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int a[] = {1, 2, 3, 4};

    int pid = fork();
    if (pid == -1)				// fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)				// in child process
    {
	a[0] += a[1];
	printf("[In CHILD] Sum: %d\n", a[0]);

	exit(0);
    }
    else
    {
	a[2] += a[3];				// in parent process

	int status;
	wait(&status);
	printf("\n[In PARENT] Child has finished with exit status: %d\n", status);

	a[0] += a[2];
	printf("[In PARENT] Sum: %d\n", a[0]);
    }

    return 0;
}