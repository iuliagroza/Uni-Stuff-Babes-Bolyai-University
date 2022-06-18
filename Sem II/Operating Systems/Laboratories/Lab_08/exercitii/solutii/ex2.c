//
// ex2.c
//
// Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură
// un număr natural şi îl trimite prin pipe procesului copil, iar procesul copil verifică şi afişează dacă acest număr este prim.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


// check if number n is prime
int is_prime(unsigned int n)
{
	if (n <= 1)
		return 0;	// zero and one are not prime

    	unsigned int i;
    	for (i = 2; i*i <= n; i++)
	{
		if (n % i == 0)
			return 0;
    	}

    	return 1;
}


int main(int argc, char* argv[])
{
	int pd[2];
	int res = pipe(pd);	// cream un pipe
	if (res == -1)
	{
		perror("pipe() error: ");
		exit(EXIT_FAILURE);
	}

	int pid = fork();	// cream procesul copil
	if (pid == -1)
	{
		perror("fork() error: ");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)		// in procesul copil
	{
		close(pd[1]);	// inchidem capatul pentru scriere

		while(1)
		{
			int n = 0;
			read(pd[0], &n, sizeof(int));	// citim din pipe

			printf("\t[In CHILD] Numarul citit este: %d\n", n);

			if (n == 0)
				break;

			//sleep(2);
		}

		// inchidem capatul pentru citire
		close(pd[0]);	// inchidem capatul pentru citire

		printf("\t[In CHILD] I finished my job.\n");

		exit(EXIT_SUCCESS);
	}
	
	// in procesul parinte
	close(pd[0]);	// inchidem capatul pentru citire

	while(1)
	{
		// citim numarul natural de la tastatura
		int n = 0;
		printf("[In PARENT] Introduceti un numar natural n: ");
		scanf("%d", &n);

		write(pd[1], &n, sizeof(int));	// scriem numarul citit in pipe

		if (n == 0)
			break;

		sleep(2);
	}

	close(pd[1]);	// inchidem capatul pentru scriere

	// asteptam terminarea procesului copil
	int status;
	wait(&status);

	printf("[In PARENT] Child has finished with exit status: %d\n", status);

	printf("[In PARENT] I finished my job.\n");

	return 0;
}
