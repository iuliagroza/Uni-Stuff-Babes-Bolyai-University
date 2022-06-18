#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{

	if (argc == 1)
	{
		printf("Error: Insufficient number of arguments.\n");
		printf("Usage: lab2_2 arg_1 arg_2 ...\n");
		return 1;
	}

	printf("Number of arguments (argc): %d\n", argc);

	for (int i=0; i < argc; i++)
	{
		printf("Argument argv[%d]: %s\n", i, argv[i]);
	}

	return 0;
}
