//
// pipe_1.c
//
// IPC - Using half-duplex pipe (pipe() system call)
//
// A half-duplex pipe resides within the kernel itself,
// and not within the bounds of any physical file system.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    int fd[2];                      // file descriptors
    int a[] = {1, 2, 3, 4};

    int res = pipe(fd);
    if (res == -1)                  // fail to create pipe
    {
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1)                  // fail to create child
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                   // in child process
    {
        close(fd[0]);               // close the read descriptor

        a[0] += a[1];
        printf("[CHILD] Sum: %d\n", a[0]);

        write(fd[1], &a[0], sizeof(int));   // write partial sum to pipe

        close(fd[1]);               // close the write descriptor
        exit(0);
    }

    close(fd[1]);                   // close the write descriptor

    a[2] += a[3];

    read(fd[0], &a[0], sizeof(int));        // read the partial sum from pipe

    int status;
    wait(&status);
    printf("[PARENT] Child has finished with exit status: %d\n", status);

    a[0] += a[2];

    printf("[PARENT] Sum: %d\n", a[0]);

    close(fd[0]);                   // close the read descriptor
    return 0;
}
