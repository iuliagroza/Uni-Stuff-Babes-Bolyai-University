//
// shm_server.c
//
// Serverul va crea segmentul de memorie partajata si va executa continuu (fara sleep) operatia de adunare sum = a + b.
// La primirea semnalului SIGINT (Ctrl-C) serverul va distruge segmentul de memorie partajata si isi va incheia executia.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>

#define SHM_KEY 0x1234	// shared memory key

struct data				// data structure
{
	int a;
	int b;
	int sum;
};

int go = 1;				// execution flag

// Handle the SIGINT signal
void stop(int sig)
{
    go = 0;
}

int main(int argc, char *argv[])
{
	signal(SIGINT, stop);					// set the SIGINT signal handler

	int id = shmget(SHM_KEY, 5 * sizeof(int), IPC_CREAT|0600);	// create the shared memory segment

  struct data *dp = (struct data*)shmat(id, 0, 0);						// attach the shared memory segment

	while (go)										// do until SIGINT
	{
		dp->sum = dp->a + dp->b;
	}

	shmdt(dp);										// detach the shared memory segment

	shmctl(id, IPC_RMID, NULL);		// destroy the shared memory segment

	return 0;
}
