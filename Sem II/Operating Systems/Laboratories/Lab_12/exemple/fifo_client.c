//
// fifo_client.c - Using a System V semaphore set (a named semaphore)
//
// Semaphores allow processes and threads to synchronize their actions.
// A semaphore is an integer whose value is never allowed to fall below zero.
// Two operations can be performed on semaphores:
// - increment the semaphore value by one;
// - decrement the semaphore value by one.
// If the value of a semaphore is currently zero, then a sem_lock() operation will block until the value becomes greater than zero.
//

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>


int sem_num = 0;	// the semaphore number (0 is the first)


int sem_op(int sid, int op, int flag)
{
	struct sembuf sb;
	sb.sem_num = sem_num;
	sb.sem_op = op;
	sb.sem_flg = flag;

	int res = semop(sid, &sb, 1);
	if(res < 0 && flag == 0)
	{
		perror("sem_op():");
	}

	return res;
}

void sem_lock(int sid)
{
	sem_op(sid, -1, IPC_NOWAIT);
}

void sem_unlock(int sid)
{
	sem_op(sid, 1, IPC_NOWAIT);
}

void sem_destroy(int sid)
{
	semctl(sid, 0, IPC_RMID, 0);
}



int main()
{
	key_t key = 1234;	// an unique key to identify the semaphore

	int sid = semget(key, 0, 0);
	if (sid < 0)
	{ 
		perror("semget(): ");
		exit(EXIT_FAILURE);
	}

	int pd = open("test-fifo", O_WRONLY);
	if (pd < 0)
	{
		perror("open(): ");
		exit(EXIT_FAILURE);
	}
	
	srand(time(NULL));
	
	int i = 0;
	while (i < 10)
	{
		int n1 = rand() % 100;
		printf("\n[Client] n1: %3d\n", n1);

		int n2 = rand() % 100;
		printf("[Client] n2: %3d\n", n2);

		printf("[Client] Trying to lock the semaphore ...\n");
		sem_lock(sid);
		printf("[Client] Semaphore locked.\n");

		write(pd, &n1, sizeof(int));
		write(pd, &n2, sizeof(int));

		printf("[Client] Trying to unlock the semaphore ...\n");
		sem_unlock(sid);
		printf("[Client] Semaphore unlocked.\n");

		sleep(2);

		i++;
	}
	
	close(pd);
	
	return 0;
} 
