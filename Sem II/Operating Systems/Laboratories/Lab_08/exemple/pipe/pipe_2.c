//
// pipe_2.c
//
// Sa se implementeze un proces care creeaza un proces copil cu care comunica
// prin pipe. Procesul parinte trimite prin pipe procesului copil doua numere
// intregi, iar procesul copil returneaza prin pipe suma lor.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    int c2p[2];                     // child to parent file descriptors
    int res = pipe(c2p);
    if (res == -1)                  // fail to create pipe
    {
        perror("pipe(c2p)");
        exit(EXIT_FAILURE);
    }

    int p2c[2];                     // parent to child file descriptors
    res = pipe(p2c);
    if (res == -1)                  // fail to create pipe
    {
        perror("pipe(p2c)");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1)                  // fail to create child
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    // in the child process
    if (pid == 0)
    {
        // close the unused file descriptors
        close(c2p[0]);
        close(p2c[1]);

        while(1)
        {
            // read first integer
            int a;
            read(p2c[0], &a, sizeof(int));
            printf("\t[CHILD] a: %d\n", a);

            // stop
            if (a == 0)
                break;

            // read the second integer
            int b;
            read(p2c[0], &b, sizeof(int));
            printf("\t[CHILD] b: %d\n", b);

            // send the sum to parent
            int sum = a + b;
            write(c2p[1], &sum, sizeof(int));

            printf("\t[CHILD] Sum: %d\n", sum);
      }

        // close the file descriptors
        close(c2p[1]);
        close(p2c[0]);
        exit(EXIT_SUCCESS);
    }

    // close the unused file descriptors
    close(c2p[1]);
    close(p2c[0]);

    while(1)
    {
        // read first integer
        int a;
        printf("[PARENT] a: ");
        scanf("%d", &a);

        // send to the child
        write(p2c[1], &a, sizeof(int));

        if (a == 0)
            break;

        sleep(2);

        // read the second integer
        int b;
        printf("[PARENT] b: ");
        scanf("%d", &b);

        // send to the child
        write(p2c[1], &b, sizeof(int));

        // read the sum from child
        int sum = 0;
        read(c2p[0], &sum, sizeof(int));

        printf("[PARENT] Sum: %d\n", sum);
    }

    // wait for child
    int status;
    wait(&status);
    printf("\n[PARENT] Child has finished with exit status: %d\n", status);

    // close the file descriptors
    close(c2p[0]);
    close(p2c[1]);

    return 0;
}
