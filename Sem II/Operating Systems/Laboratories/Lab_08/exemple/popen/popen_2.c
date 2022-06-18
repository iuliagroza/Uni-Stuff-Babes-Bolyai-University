//
// popen_2.c
//
// A command-line interpreter example using system() or popen()
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255


int main(int argc, char* argv[])
{
    while(1)
    {
        // display the prompt
        printf("> ");

        // read the command line
        char c; int i = 0; char cmd_line[MAX_SIZE];
        while((c = getc(stdin)) != '\n')
        {
            cmd_line[i] = c;
            i++;
        }
        cmd_line[i] = '\0';

        if (strcmp(cmd_line, "exit") == 0)
    	    break;

        //printf("Command: %s\n", cmd_line);

	// run the command using system()
	system(cmd_line);

/*
        // run the command using popen()
        FILE* fd = popen(cmd_line, "r");
        if (fd == NULL)
        {
            perror("popen()");
        }
        else
        {
            // read the output
            int ch;
            while ((ch = fgetc(fd)) != EOF)
            {
                putchar(ch);
            }

            // wait for the associated process to finish
            pclose(fd);
        }
*/
    }

    return 0;
}
