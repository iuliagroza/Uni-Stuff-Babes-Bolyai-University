#include <stdio.h>
#include <stdbool.h>

void dataTypes()
{
	printf("Char: %d\n", sizeof(char));
	printf("Bool: %d\n", sizeof(bool));
	printf("Short: %d\n", sizeof(short));
	printf("Int: %d\n", sizeof(int));
	printf("Unsigned int: %d\n", sizeof(unsigned int));
	printf("Long: %d\n", sizeof(long));
	printf("Float: %d\n", sizeof(float));
    printf("Double: %d\n", sizeof(double));
    printf("Long double: %d\n", sizeof(long double));

	// pointers
	printf("Pointer to char: %d\n", sizeof(char*));
	printf("Pointer to int: %d\n", sizeof(int*));
	printf("Pointer to double: %d\n", sizeof(double*));
}

//int main() {
//    dataTypes();
//    return 0;
//}