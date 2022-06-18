//
// ex1.c
//
// Se dă un tablou care conține 100.000 de numere întregi.
// Folosind un număr potrivit de thread-uri și cele mai potrivite mecanisme de sincronizare,
// să se determine cel mai mic număr întreg din acest tablou.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define MAX_THR 50
#define MAX_NUM 100000

int minims[MAX_THR];
int numbers[MAX_NUM];


void* do_work(void *a)
{
	int tnum = *(int *)a;

	int i;
	int min = INT_MAX;
	int st = tnum * (MAX_NUM/MAX_THR);
	int dr = st + MAX_NUM/MAX_THR;
	for (i = st; i < dr; i++)
	{
		if (numbers[i] < min)
			min = numbers[i];
	}
	
	printf("[Thread %d] minim: %d\n", tnum, min);
	
	// stocam minimul local
	minims[tnum] = min;

	free(a);

	return NULL;
}


int main(int argc, char *argv[])
{
	// // generam 100.000 numere aleatoare
	// int i;
	// srand(time(NULL));
	// for (i = 0; i < MAX_NUM; i++)
	// {
	// 	numbers[i] = rand() % 20;
	// }

	// deschidem fisierul binar
	int fd = open("random-file.bin", O_RDONLY);

	// citim 100.000 numere
	int i;
	for (i = 0; i < MAX_NUM; i++)
	{
		read(fd, &numbers[i], 2);
	}

	// cream thread-urile
	pthread_t tid[MAX_THR];
	for (i = 0; i < MAX_THR; i++)
	{
		int *n = (int *)malloc(sizeof(int));
		*n = i;
		pthread_create(&tid[i], NULL, do_work, n);
	}

	// asteptam terminarea thread-urilor
	for (i = 0; i < MAX_THR; i++)
	{
		pthread_join(tid[i], NULL);
	}

	// determinam minimul
	int min = INT_MAX;
	for (i = 0; i < MAX_THR; i++)
	{
		if (minims[i] < min)
			min = minims[i];
	}
	printf("Minim:  %d\n", min);

	close(fd);

	return 0;
}
