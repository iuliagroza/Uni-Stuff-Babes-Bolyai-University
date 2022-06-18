#include <stdio.h>


int main(int argc, char *argv[])
{
	char c;
	char buffer[50];
	char filename[] = "test.txt";

	// open the file
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Error: ");
		return 1;
	}

	// read the file content char by char
	printf("Trying to read file char by char...\n");
	while ((c = fgetc(file)) != EOF)
	{
		printf("%c", c);
	}

	rewind(file);
	//fseek(file, 0L, SEEK_SET);

	// read the file content using a buffer
	printf("Trying to read file using a buffer...\n");
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		printf("%s", buffer);
	}

	// close the file
	fclose(file);
	
	return 0;
}
