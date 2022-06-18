#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


//
// Alocate the memory for a 2D array
//
void allocate_array(int rows, int cols, int **array)
{
	array = (int **)malloc(rows * sizeof(int *));
	if (array == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < rows; i++)
	{
		array[i] = (int *)malloc(cols * sizeof(int));
		if (array[i] == NULL)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
}


//
// Print a 2D array line by line
//
void print_array(int rows, int cols, int **array)
{
	for (int i = 0; i < rows; i++)
	{
		printf ("( ");
		for (int j = 0; j < cols; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf(")\n");
	}
}


int main(int argc, char *argv[])
{
	int nrows = 3;							// number of rows
	int ncols = 4;							// number of columns
	int **matrix;							// a 2D array

	//allocate_array(nrows, ncols, matrix);

	// alocate the memory for the matrix
	matrix = (int **)malloc(nrows * sizeof(int *));
	if (matrix == NULL)
	{
		perror("Error");
		return 1;
	}

	for (int i = 0; i < nrows; i++)
	{
		matrix[i] = (int *)malloc(ncols * sizeof(int));
		if (matrix[i] == NULL)
		{
			perror("Error");
			return 1;
		}
	}

	char c;
	char filename[] = "matrix.txt";

	// open the text file
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	int j = 0;

	// read the content of file char by char
	while ((c = fgetc(file)) != EOF)
	{
		if (!isspace(c))
		{
			matrix[i][j] = (c - 48);

			j++;
			if (j == ncols)
			{
				i++;
				j = 0;
			}
		}

		if (i == nrows)
			break;
	}

	// display the matrix
	print_array(nrows, ncols, matrix);

	// deallocate the memory used for matrix
	for (int i = 0; i < nrows; i++)
		free (matrix[i]);

	free(matrix);

	return 0;
}
