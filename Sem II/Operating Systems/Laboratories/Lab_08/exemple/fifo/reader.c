//
// reader.c
//
// Using named pipe (FIFO) - Read from a FIFO
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 1024


int main(int argc, char* argv[])
{
    // set the FIFO path
    char* fifo1 = "./fifo1";

    // open the FIFO for read
    int fd = open(fifo1, O_RDONLY);
    if (fd == -1)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    // read message from FIFO
    char buf[MAX_BUF];
    read(fd, buf, MAX_BUF);
    printf("Message: %s\n", buf);

    // close the FIFO
    close(fd);

    return 0;
}
