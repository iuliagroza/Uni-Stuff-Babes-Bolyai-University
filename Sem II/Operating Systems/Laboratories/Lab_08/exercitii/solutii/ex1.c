//
// ex1.c
//
// Să se scrie un program C care creează un proces copil cu care comunică prin pipe.
// Procesul părinte citeşte de la tastatură un număr natural şi îl trimite prin pipe
// procesului copil, iar procesul copil verifică şi afişează dacă acest număr este par sau impar.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	int n, fd[2];

	int res = pipe(fd);
	if (res == -1)			// failed to create pipe
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}

	int pid = fork();
	if (pid == -1)			// fork() failed
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	// in the child process
    if (pid == 0)
    {
		close(fd[1]);		// close the write descriptor

		while(1)
		{
			read(fd[0], &n, sizeof(int));

			if (n == 0)
				break;

			printf("[CHILD] n = %d\n", n);

			if (n % 2 == 0)
				printf("[CHILD] n este par.\n");
			else
				printf("[CHILD] n este impar.\n");

			sleep(2);
		}

		close(fd[0]);		// close the read descriptor

		exit(EXIT_SUCCESS);
    }

    // in the parent process
    while(1)
    {
		close(fd[0]);		// close the read descriptor

		printf("n: ");
		scanf("%d", &n);

		write(fd[1], &n, sizeof(int));

		if (n == 0)
			break;

		sleep(2);
    }

	int status;
	wait(&status);			// wait for child to finish

	close(fd[1]);			// close the write descriptor

	return 0;
}
