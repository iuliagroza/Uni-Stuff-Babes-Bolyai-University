//
// popen_1.c
//
// Using popen() system call
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
    // if user has not provided an argument
    if (argv[1] == NULL)
    {
        printf("You need to provide a file name.\n");
        printf("Usage: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // build the command to execute
    char cmd[50];
    strncat(cmd, "cat ", 4);
    strncat(cmd, argv[1], strlen(argv[1]));

    printf("Command: %s\n", cmd);

    // call popen()
    FILE* fd = popen(cmd, "r");
    if (fd == NULL)
    {
        perror("popen()");
        exit(EXIT_FAILURE);
    }

    // read the output
    int ch;
    while ((ch = fgetc(fd)) != EOF)
    {
        putchar(ch);
    }

    // wait for the associated process to finish
    pclose(fd);

    return 0;
}
