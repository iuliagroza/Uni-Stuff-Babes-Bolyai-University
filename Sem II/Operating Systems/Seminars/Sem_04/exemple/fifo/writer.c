//
// Using named pipe (FIFO) - Create and write to a FIFO
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    	char* fifo1 = "./fifo1";	// FIFO path

    	// create the FIFO (named pipe)
    	int res = mkfifo(myfifo, 0666);
    	if (res == -1)
    	{
        	perror("mkfifo() error: ");
        	exit(EXIT_FAILURE);
    	}

   	// open the FIFO
    	int fd = open(fifo1, O_WRONLY);
    	if (fd == -1)
    	{
        	perror("open() error: ");
        	exit(EXIT_FAILURE);
    	}

    	// write a string to the FIFO
    	char msg[] = "Hello from FIFO";
    	write(fd, msg, sizeof(msg));

    	close(fd);

    	// remove the FIFO
    	unlink(myfifo);

    	return 0;
}
