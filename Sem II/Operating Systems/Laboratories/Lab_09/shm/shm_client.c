//
// shm_client.c
//
// Clientul se va conecta la zona de memorie partajata, va da variabilelor a si b valori aleatoare intre 0 si 9 si va afisa
// pe ecran valorile a, b si sum.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_KEY 0x1234	// shared memory key

struct data				// memory data structure
{
	int a;
	int b;
	int sum;
};


int main(int argc, char *argv[])
{
	int id = shmget(SHM_KEY, 0, 0);						// get the ID of the shared memory segment

	struct data *dp = (struct data*)shmat(id, 0, 0);	// attach to the shared memory segment

	int i;
	for (i = 0; i < 10; i++)
	{
		dp->a = rand() % 10;
		dp->b = rand() % 10;

		//sleep(2);

		printf("[Client] %d + %d = %d\n", dp->a, dp->b, dp->sum);
	}

	shmdt(dp);											// detach from the shared memory segment

	return 0;
}