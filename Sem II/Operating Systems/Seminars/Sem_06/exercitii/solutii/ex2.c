//
// ex2.c
//
// Se dă un tablou care conține 100.000 de numere întregi.
// Folosind un număr potrivit de thread-uri și cele mai potrivite mecanisme de sincronizare,
// să se determine diferența absolută dintre minimul local și media aritmetică a valorilor minime
// determinate pe fiecare interval de 2000 de numere întregi.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

#define MAX_THR 50
#define MAX_NUM 100000

int minims[MAX_THR];
int numbers[MAX_NUM];

pthread_barrier_t barr;

void* do_work(void *a)
{
	int tnum = *(int *)a;
	free(a);

	int i;
	int min = INT_MAX;
	int st = tnum * (MAX_NUM/MAX_THR);
	int dr = st + MAX_NUM/MAX_THR;
	for (i = st; i < dr; i++)
	{
		if (numbers[i] < min)
			min = numbers[i];
	}

	// stocam minimul local
	minims[tnum] = min;
	printf("[Thread %2d] a ajuns la bariera.\n", tnum);

	pthread_barrier_wait(&barr);

	// determinam media aritmetica
	int sum = 0;
	for (i = 0; i < MAX_THR; i++)
		sum += minims[i];
	float mean = sum/MAX_THR;

	float diff = fabs(mean - min);
	printf("[Thread %2d] min: %d medie: %f diferenta: %f\n", tnum, min, mean, diff);

	return NULL;
}


int main(int argc, char *argv[])
{
	// // generam 100.000 numere aleatoare
	// int i;
	// srand(time(NULL));
	// for (i = 0; i < MAX_NUM; i++)
	// {
	//      numbers[i] = rand() % 20;
	// }

	// deschidem fisierul binar
	int fd = open("random-file.bin", O_RDONLY);

	// citim 100.000 numere
	int i;
	for (i = 0; i < MAX_NUM; i++)
	{
		read(fd, &numbers[i], 2);
	}

	// cream bariera
	pthread_barrier_init(&barr, NULL, MAX_THR);

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

	pthread_barrier_destroy(&barr);
	close(fd);

	return 0;
}
