//
// Using variables defined in parent process and passing status
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LEN 10

int main(int argc, char* argv[])
{
    int sum = 0;

    int *numbers = (int*)malloc(MAX_LEN * sizeof(int));
    if (numbers == NULL)
    {
        perror("malloc() error: ");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < MAX_LEN; i++)
        numbers[i] = i;


    int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                       // in child process
    {
        printf("\n[In CHILD] I started...\n");
        printf("[In CHILD] My PID is %d\tParent PID is %d\n", getpid(), getppid());

        for (i = 0; i < MAX_LEN; i++)
            if ( numbers[i] % 2 == 0 )
                sum += numbers[i];

        printf("[In CHILD] Sum: %d\n", sum);

        printf("[In CHILD] I finished my job.\n");
        exit(sum);
    }
    else                                // in parent process
    {
        printf("[In PARENT] I started ...\n");
        printf("[In PARENT] My PID is %d\tChild PID is %d\n", getpid(), pid);

        int status;
        wait(&status);
        printf("\n[In PARENT] Child has finished with exit status: %d\n", status);

        sum = WEXITSTATUS(status);
        printf("[In PARENT] Sum from CHILD: %d\n", sum);

        for (i = 0; i < MAX_LEN; i++)
            if ( numbers[i] % 2 == 1 )
                sum += numbers[i];

        printf("[In PARENT] Final sum: %d\n", sum);
        printf("[In PARENT] I finished.\n");
    }

    return 0;
}
