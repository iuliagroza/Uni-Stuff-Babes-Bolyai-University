//
// msg_server.c
//
// Serverul va crea coada de mesaje la pornire si va trata intr-un ciclu infinit mesajele de la clienti.
// La primirea semnalului SIGINT (Ctrl-C) serverul va distruge coada de mesage si isi va incheia executia.
//

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define MSG_KEY 0x1234	// message queue key

struct msgbuf
{
	long mtype;
	int mtext;
};

int go = 1;	// execution flag

// Handle the SIGINT signal
void stop(int sig)
{
    go = 0;
}


int main(int argc, char *argv[])
{
	signal(SIGINT, stop);												// set the SIGINT signal handler

	int id = msgget(MSG_KEY, IPC_CREAT | 0600);							// create the message queue

	struct msgbuf rbuf;													// create and fill the message to send
	rbuf.mtype = 1;
	rbuf.mtext = 0;

	while (go)															// do until SIGINT
	{
		msgrcv(
			id,
			&rbuf, sizeof(rbuf.mtext), rbuf.mtype,
			MSG_NOERROR | IPC_NOWAIT);

		if (rbuf.mtext > 0)
		{
			printf("Received: %d\n", rbuf.mtext);

			struct msgbuf sbuf;											// create receive buffer
			sbuf.mtype = 1;
			sbuf.mtext = 2 * rbuf.mtext;

			msgsnd(
				id,
				&sbuf, sizeof(sbuf.mtext),
				IPC_NOWAIT);
			printf("Sent: %d\n", sbuf.mtext);

			rbuf.mtext = 0;
		}

		sleep(2);
	}

	msgctl(id, IPC_RMID, NULL);											// destroy the message queue

	return 0;
}
