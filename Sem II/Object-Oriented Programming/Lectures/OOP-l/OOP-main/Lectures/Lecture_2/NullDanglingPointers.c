#include <stdio.h>


int* f()
{
	int localVar = 7;
	printf("Value of local variable in function: %d.\n", localVar);
	return &localVar;
}

int nullDanglingPointers()
{
	int* p1 = NULL;

	if (p1 == NULL)
		printf("p1 is NULL.\n");

	// try to dereference p1 -> Error
	//printf("The value at the address pointed to by p1 is: %d", *p1);

	// before dereferencing a pointer, always check whether or not it is null
	if (p1 != NULL)
		printf("The value at the address pointed to by p1 is: %d.\n", *p1);

	// ------------------------------------------------------------------------------------
	// Dangling pointer
	int* p2 = f();
	// printf("p2: %d.\n", *p2); // this is undefined behaviour!!!

	int* p3 = NULL;
	{
		int x = 10;
		p3 = &x;
		printf("p3: %d.\n", *p3);
	}

	// p3 is now a dangling pointer
	// printf("p3: %d.\n", *p3);
	return 0;
}

//int main() {
//	nullDanglingPointers();
//	return 0;
//}