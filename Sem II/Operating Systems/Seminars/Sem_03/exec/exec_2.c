//
// Using execv(), execvp() system calls
//
// int execv(const char *path, char *const argv[])
// int execvp(const char *file, char *const argv[])
//
// execvp() has the same purpose except that it will use environment variable PATH to determine which executable to process
//

#include <stdio.h>
#include <unistd.h>

int main()
{
	char *args[] = {"/bin/ls", "-r", "-t", "-l", NULL};
	//char *args[] = {"/bin/ls", "-r", "-t", "-l", (char *) 0 };

	//printf("[In main()] Calling execv() ...\n");
	//execv(args[0], args);

	printf("[In main()] Calling execvp() ...\n");
	execvp("ls", args);

	printf("[In main()] I finished.\n");
	return 0;
}