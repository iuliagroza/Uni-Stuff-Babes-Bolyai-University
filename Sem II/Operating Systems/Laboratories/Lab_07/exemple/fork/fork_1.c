//
// Using fork() to create a child process
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
 
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
        printf("[In CHILD]\tMy PID is %d\tParent PID is %d\n", getpid(), getppid());
    }
    else                                // in parent process
    {
        printf("[In PARENT]\tMy PID is %d\tChild PID is %d\n", getpid(), pid);
    }

    return 0;
}
