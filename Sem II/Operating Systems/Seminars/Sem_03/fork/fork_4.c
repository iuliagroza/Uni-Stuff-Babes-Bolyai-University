//
// Using wait() system call (man 2 wait)
//
// If the parent process calls wait() system call,
// then the execution of parent is suspended until the child is terminated.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                       // in child process
    {
        printf("[In CHILD] I started ...\n");
        printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
        sleep(10);
        printf("[In CHILD]\tI am NOT an ORPHAN process ...\n");
        printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
        printf("[In CHILD] I finished my job.\n");
    }
    else                                // in parent process
    {
        printf("[In PARENT] I started ...\n");
        printf("[In PARENT]\tMy PID is %d Child PID is %d\n", getpid(), pid);
        int status;
        wait(&status);
        printf("[In PARENT]\tChild has finished with exit status: %d\n", status);
        printf("[In PARENT] I finished.\n");
    }

    return 0;
}
