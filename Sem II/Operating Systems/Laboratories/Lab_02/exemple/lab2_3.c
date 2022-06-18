#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
	int i = 0;

	printf("Environment variables:\n");
	while (env[i])
	{
		printf("env[%d]: %s\n", i, env[i]);
		i++;
	}

	return 0;
}
