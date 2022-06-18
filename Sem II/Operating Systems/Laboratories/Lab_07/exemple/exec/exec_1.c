//
// Using execl(), execlp() system calls
//
// int execl(const char *path, const char *arg0, const char *arg1, const char *arg2, ... const char *argn, NULL);
//
// execlp() has the same purpose except that it will use environment variable PATH to determine which executable to process
//

#include <stdio.h>
#include <unistd.h>

int main()
{
	//printf("[In main()] Calling execl() ...\n");

	//execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", NULL);
	//execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", (char *) 0);

	printf("[In main()] Calling execlp() ...\n");
	
	execlp("ls", "ls", "-r", "-t", "-l", NULL);

	printf("[In main()] I finished.\n");
	return 0;
}