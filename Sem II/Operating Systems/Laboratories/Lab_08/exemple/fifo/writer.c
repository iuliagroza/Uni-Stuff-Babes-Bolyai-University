//
// writer.c
//
// Using named pipe (FIFO) - Create and write to a FIFO
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    // set the FIFO path
    char* fifo1 = "./fifo1";

    // create the FIFO (named pipe)
    int res = mkfifo(fifo1, 0644);
    if (res == -1)
    {
        perror("mkfifo()");
        exit(EXIT_FAILURE);
    }

    // open the FIFO for write
    int fd = open(fifo1, O_WRONLY);
    if (fd == -1)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    // write a string to the FIFO
    char msg[] = "Hello from FIFO";
    write(fd, msg, sizeof(msg));

    // close the FIFO
    close(fd);

    // remove the FIFO
    unlink(fifo1);

    return 0;
}
