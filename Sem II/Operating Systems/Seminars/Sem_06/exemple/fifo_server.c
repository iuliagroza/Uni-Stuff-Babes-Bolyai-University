//
// fifo_server.c - Using a System V semaphore set (a named semaphore)
//
// Semaphores allow processes and threads to synchronize their actions.
// A semaphore is an integer whose value is never allowed to fall below zero.
// Two operations can be performed on semaphores:
// - increment the semaphore value by one;
// - decrement the semaphore value by one.
// If the value of a semaphore is currently zero, then a sem_lock() operation will block until the value becomes greater than zero.
//
// Launch this program first in order to create the semaphore set.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
	int nsems = 1;		// the number of semaphores in the semaphore set
	key_t key = 1234;	// an unique key to identify the semaphore set

	printf("[Server] Trying to create a semaphore ...\n");

	int sid = semget(key, nsems, IPC_CREAT | 0666);
	if (sid < 0)
	{ 
		perror("semget(): ");
		exit(EXIT_FAILURE);
	}

	printf("[Server] Semaphore created.\n");

	// set the initial semaphore value to 1
	semctl(sid, sem_num, SETVAL, 1);

	int pd = open("test-fifo", O_RDONLY);
	if (pd < 0)
	{
		perror("open(): ");
		exit(EXIT_FAILURE);
	}
	
	while (1)
	{
		int n1, n2;
		
		printf("\n[Server] Trying to lock the semaphore ...\n");
		sem_lock(sid);
		printf("[Server] Semaphore locked.\n");

		int rc = read(pd, &n1, sizeof(int));
		if (rc == 0)
		{
			printf("\n[Server] Client has gone. Trying to break ...\n");
			break;
		}

		read(pd, &n2, sizeof(int));

		printf("[Server]  n1: %3d\n", n1);
		printf("[Server]  n2: %3d\n", n2);
		printf("[Server] Sum: %3d\n", n1 + n2);
		
		printf("[Server] Trying to unlock the semaphore ...\n");
		sem_unlock(sid);
		printf("[Server] Semaphore unlocked.\n");

		sleep(2);
	}
	
	close(pd);

	printf("\n[Server] Trying to destroy the semaphore ...\n");
	sem_destroy(sid);
	printf("[Server] Semaphore destroyed.\n");

	return 0;
} 
