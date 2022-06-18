//
// dup_1.c
//
// An example of output redirection using dup2() system call
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    // check the command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // create the file for write
    int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1)                   // open failed
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    printf("This text goes to the standard output.\n");
    printf("Now the standard output will go to \"%s\".\n", argv[1]);

    // standard output is file descriptor 1
    // we use dup2() to copy our file descriptor onto file descriptor 1
    // dup2() will close the current standard output
    dup2(fd, 1);

    printf("This text goes to the standard output too.\n");

    close(fd);

    return 0;
}
