#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "f2"

int main() {
	if(mkfifo(FIFO, 0600) < 0) {
		perror("Unable to create FIFO channel.");
		exit(1);
	}

	int fd = open(FIFO, O_WRONLY);
	if(fd < 0) {
		perror("Unable to open FIFO.");
		exit(3);
	}

	int r=rand()%10;

	printf("We are sending: %d\n", r);

	if(write(fd, &r, sizeof(int)) < 0) {
		perror("Unable to write int.");
		exit(4);
	}


	if(unlink(FIFO) < 0) {
		perror("Unable to delete FIFO channel.");
		exit(2);
	}
	printf("Done\n");
	return 0;
}
