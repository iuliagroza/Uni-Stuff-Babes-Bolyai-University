#include <stdio.h>
#include <stdlib.h>
//#include <crtdbg.h>

int dynamicMemoryManagement()
{
	//allocate memory on the heap for an int
	int* p = (int*)malloc(sizeof(int));
	*p = 7;
	printf("Value at address p: %d,\n", *p);
	//Deallocate
	free(p);

	//allocate space for n ints (array) - this cannot be made statically (try int arr[n])
	int n = 0;
	printf("Input the length for your array: ");
	scanf("%d", &n);
	int* arr = (int*)malloc(n * sizeof(int));
	arr[0] = 0;
	arr[1] = 1;
	printf("Second element of the array: %d. \n", arr[1]);

	//dealocate
	free(arr);

	// Memory leak
	p = NULL;
	for (int i = 0; i < 10; i++)
	{
		p = (int*)malloc(sizeof(int));
		//allocate memory for an int on the heap
		*p = i * 2;
		printf("Value of p: %d.\n", *p);
	}
	free(p); //deallocate memory
			 //leaked memory - we only deallocated the last int

	// Only works on Visual Studio C++ compiler!
	//_CrtDumpMemoryLeaks();

	return 0;
}

//int main() {
//	dynamicMemoryManagement();
//	return 0;
//}