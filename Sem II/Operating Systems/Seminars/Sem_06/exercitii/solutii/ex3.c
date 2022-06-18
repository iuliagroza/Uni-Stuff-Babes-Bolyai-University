//
// ex3.c
//
// Se dau un fișier binar care conține 100.000 de numere aleatoare și un tablou care poate stoca doar 100 de numere.
// Să se determine suma primelor 1000 de numere întregi din acest fișier folosind 10 thread-uri (consumers threads).
// Citirea celor 1000 de numere intregi se va face, pe rând, în variabila buffer folosind alte 10 thread-uri (producers threads).
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_THR 10
#define MAX_SIZE 100

int fd;					// the file descriptor must be GLOBAL

int sum = 0;
int state = 0;			// buffer state: 0 - empty, 1 - full
int buf[MAX_SIZE];

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


// producer threads
void* produce(void* a)
{
	pthread_mutex_lock(&mtx);
	while (state == 1)					// if buffer state is FULL
		pthread_cond_wait(&cv, &mtx);	// wait for buffer to become EMPTY

	int i;
	for (i = 0; i < MAX_SIZE; i++)
		read(fd, &buf[i], 1);

	state = 1;							// buffer is FULL
	pthread_cond_broadcast(&cv);
	pthread_mutex_unlock(&mtx);

	return NULL;
}


// consumer threads
void* consume(void* a)
{
	pthread_mutex_lock(&mtx);
	while (state == 0)					// if buffer state is EMPTY
		pthread_cond_wait(&cv, &mtx);	// wait for buffer to become FULL

	int i;
	for (i = 0; i < MAX_SIZE; i++)
		sum += buf[i];

	state = 0;							// buffer is EMPTY
	pthread_cond_signal(&cv);
	pthread_mutex_unlock(&mtx);

	return NULL;
}


int main(int argc, char* argv[])
{
	fd = open("file.bin", O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		exit(1);
	}

	int i;
	pthread_t ctid[MAX_THR];
	pthread_t ptid[MAX_THR];
	for (i = 0; i < MAX_THR; i++)
	{
		pthread_create(&ctid[i], NULL, consume, NULL);
		pthread_create(&ptid[i], NULL, produce, NULL);
	}

	for (i = 0; i < MAX_THR; i++)
	{
		pthread_join(ctid[i], NULL);
		pthread_join(ptid[i], NULL);
	}

	printf("Suma: %d\n", sum);

	close(fd);
	
	return 0;
}
