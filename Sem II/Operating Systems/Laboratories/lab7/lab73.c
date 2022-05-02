#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "f2"

int main() {
	int fd = open(FIFO, O_RDONLY);
	if(fd < 0) {
		perror("Unable to open FIFO.");
		exit(3);
	}

	int r;

	if(read(fd, &r, sizeof(int)) < 0) {
		perror("Unable to read int.");
		exit(4);
	}


	if(unlink(FIFO) < 0) {
		perror("Unable to delete FIFO channel.");
		exit(2);
	}
	printf("We received: %d \n", r);
	exit(0);
	return 0;
}
