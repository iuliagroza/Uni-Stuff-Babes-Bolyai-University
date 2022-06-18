//
// msg_client.c
//
// Clientul va trimite serverului un intreg, iar serverul il va trimite inapoi dublat.
//

#include <stdio.h>
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


int main(int argc, char *argv[])
{
	int id = msgget(MSG_KEY, 0);						// get the ID of the message queue

	struct msgbuf msg;									// create and fill the message buffer
	msg.mtype = 1;

	printf("Dati un intreg: ");							// read an integer
	scanf("%d", &msg.mtext);

	msgsnd(
		id,
		&msg, sizeof(msg.mtext),
		IPC_NOWAIT);									// send the message
	printf("Sent: %d\n", msg.mtext);

	sleep(2);

	msgrcv(
		id,
		&msg, sizeof(msg.mtext), msg.mtype,
		MSG_NOERROR | IPC_NOWAIT);						// receive the message
	printf("Received: %d\n", msg.mtext);

	return 0;
}