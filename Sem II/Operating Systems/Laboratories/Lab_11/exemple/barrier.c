//
// barrier.c - Using barriers
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THR_NUM 5		// number of threads
#define VAL_NUM 5		// numbers of integers in the array

int values[VAL_NUM];

pthread_barrier_t barr;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


//
// List array
//
void list_values(int id)
{
	pthread_mutex_lock(&mtx);
	
	int i;
	printf("[Thread %2d] The values are:", id); 
	for (i = 0; i < VAL_NUM; i++)
	{
		printf(" %d", values[i]);
	}
	printf("\n");

	pthread_mutex_unlock(&mtx);
}

//
// Thread routine
//
void* do_work(void* a)
{
	int id = *(int*)a;
	free(a);

	sleep(2);

	pthread_mutex_lock(&mtx);

	printf("[Thread %2d] Enter a value: ", id);
	scanf("%d", &values[id]);

	pthread_mutex_unlock(&mtx);

	// wait until each thread execute the code above this point
	pthread_barrier_wait(&barr);
	
	list_values(id);

	return NULL;
}



int main(int argc, char* argv[])
{
	pthread_barrier_init(&barr, NULL, THR_NUM);		// init the barrier

	int i;
	pthread_t tid[THR_NUM];
	for (i = 0; i < THR_NUM; i++)
	{
		int *id = (int*)malloc(1 * sizeof(int));
		*id = i;

		int rc = pthread_create(&tid[i], NULL, do_work, id);
		if (rc != 0)
			printf("Unable to create thread %2d\n", id);
	}

	printf("The threads were created.\n");
	
	for (i = 0; i < THR_NUM; i++)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_barrier_destroy(&barr);					// destroy the barrier

	return 0;
}
