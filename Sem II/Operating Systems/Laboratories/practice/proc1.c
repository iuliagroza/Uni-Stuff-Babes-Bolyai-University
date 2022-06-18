#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 10

int main()
{
    for(int i=0; i<N; i++) {
        int f = fork();
        if(f < 0) {
            perror("Unable to create child process.");
            exit(1);
        }
        if(f == 0) {
            // Child process
            printf("%d. Child - PID: %d; PPID: %d\n", i+1, getpid(), getppid());
            exit(0);
        } else {
            // Parent process
            printf("%d. Parent - PID: %d, Child PID: %d\n", i+1, getpid(), f);
        }
    }

    for(int i=0; i<N; i++) {
        wait(0);
    }
    printf("Done!\n");
    return 0;
}

