//
// Using dup2() system call - Simple example of output redirection
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int fd;							// file descriptor

    // check the arguments
    if (argc != 2)
    {
	fprintf(stderr, "Usage: %s output_file\n", argv[0]);
	exit(EXIT_FAILURE);
    }

    // open the file
    int fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
    if (fd == -1)						// open failed
    {
	perror("open() error: ");
	exit(EXIT_FAILURE);
    }

    printf("This text goes to the standard output.\n");
    printf("Now the standard output will go to \"%s\".\n", argv[1]);

    // standard output is file descriptor 1, so we use dup2()
    // to copy our file descriptor onto file descriptor 1
    // dup2() will close the current standard output
    dup2(fd, 1); 

    printf("This goes to the standard output too.\n");

    close(fd);
    return 0;
}
