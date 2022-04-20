#include <stdio.h>

void convertor(int, int);

int main()
{
	const int SIZE = 10;
	int numbers[10] = { 1, 0, 23, 455, 16, 17, 5, 20, 32, 150 };

	printf("The list of numbers in base 2:\n");

	for (int i = 0; i < SIZE; i++) {
		convertor(numbers[i], 2);
	}

	printf("\nThe list of numbers in base 16:\n");

	for (int i = 0; i < SIZE; i++) {
		convertor(numbers[i], 16);
	}
}