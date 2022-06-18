/*

ex1.c

Scrieți un program C care primește în linia de comandă oricâte perechi de argumente formate dintr-un nume de fișier și o cifră, astfel:

./ex1 a.txt 3 b.txt 3 ...

Programul va utiliza un vector cu 10 numere întregi ca variabilă globală și pentru fiecare pereche de argumente furnizată în linia de comandă, programul va crea câte un thread. Fiecare thread va determina și va adăuga numărul de litere mari din fișierul dat la numărul întreg a cărui poziție este egală cu cifra primită ca argument.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_SIZE 10		// number of elements in the array

// shared variable
int counts[MAX_SIZE];

// lock object
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct tdata
{
	int pos;
	char file[50];
};

// thread start routine
void* do_count(void* a)
{
	struct tdata targs = *(struct tdata*)a;
	free(a);

	printf("Pos: %d File: %s\n", targs.pos, targs.file);

	int fd = open(targs.file, O_RDONLY);

	char c;
	int count = 0;
	while(read(fd, &c, 1) != 0)
	{
		if((c >= 'A') && (c <= 'Z'))
			count++;
	}

	close(fd);

	pthread_mutex_lock(&mtx);
	counts[targs.pos] += count;
	pthread_mutex_unlock(&mtx);

	return NULL;
}


int main(int argc, char* argv[])
{
	// verific daca am argumente
	if (argc == 1)
	{
		printf("Not enough arguments.\n");
		printf("Usage: %s a.txt 3 b.txt 1 ...\n", argv[0]);
		exit(1);
	}

	// compute the number of required threads
	int max_thr = (int)(argc/2);

	int i;
	pthread_t tid[max_thr];
	for (i = 0; i < max_thr; i++)
	{
		struct tdata* targs = (struct tdata*)malloc(sizeof(struct tdata));
		targs->pos = atoi(argv[2*i+2]);
		strcpy(targs->file, argv[2*i+1]);
		pthread_create(&tid[i], NULL, do_count, targs);
	}

	for (i = 0; i < max_thr; i++)
	{
		pthread_join(tid[i], NULL);
	}

	printf("Counts:\n");
	for (i = 0; i < MAX_SIZE; i++)
		printf("counts[%d]: %d\n", i, counts[i]);

	return 0;
}
