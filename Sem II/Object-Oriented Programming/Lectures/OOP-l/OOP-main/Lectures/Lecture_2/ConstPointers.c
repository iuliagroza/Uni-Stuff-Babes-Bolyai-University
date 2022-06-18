#include <stdio.h>

int constPointers()
{
	int a = 9;
	const int* p1 = &a; // the pointed value cannot be changed
	//*p1 = 10; // Error - the value CANNOT be changed
	int b = 8;
	p1 = &b;  // OK - the pointer can be changed to point somewhere else

	int* const p2 = &a;	// the value can be changed, but NOT the pointer
	*p2 = 10;	// OK - the value can be changed
	//p2 = &b; // Error - the pointer CANNOT be changed to point somewhere else

	const int* const p3 = &a; // neither the value, not the pointer can be changed
	//*p3 = 11;	// Error
	//p3 = &b;	// Error

	return 0;
}

//int main() {
//	constPointers();
//	return 0;
//}