#include <iostream>

int dynamicMemMgmtCPP()
{
	int a = 1;
	int* p1 = new int;		//value from address p1 is not initialized
	std::cout << "Value at address p1: " << *p1 << std::endl;
	int* p2 = new int{ 3 };	//value from address p2 is 3
	std::cout << "Value at address p2: " << *p2 << std::endl;
	int* p3 = new int[4];	//a vector of 4 integer elements is allocated
	p3[0] = 0;
	p3[1] = 1;
	for (int i = 0; i < 2; i++)
	{
		std::cout << "Value at address p3[" << i << "]:" << p3[i] << std::endl;
	}

	//free the memory
	delete p1;
	delete p2;
	delete[] p3;

	return 0;
}

//int main() {
//	dynamicMemMgmtCPP();
//	return 0;
//}