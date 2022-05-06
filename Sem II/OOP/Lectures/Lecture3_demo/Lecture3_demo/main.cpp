#include "Vector2D.h"
#include <iostream>
#include <Windows.h>

#define PI 3.14159265
#include<cmath>

int main()
{
	system("color f4");

	//Vector2D v1{ 1, 1 };	// aggregate initialization
	//Vector2D v2;			// uninitialised: x and y coordinates contain garbage!
	//v2.xCoordinate = 2;
	//v2.yCoordinate = 3;

	//Vector2D v3{}; // x and y coordinates are initialised with default values for their types (0 - for doubles)

	//v1.add(v2);
	//std::cout << "x and coordinates for v1: (" << v1.xCoordinate << ", " << v1.yCoordinate << ")" << std::endl;

	//v1.rotate(PI / 3);
	//std::cout << "x and coordinates for v1: (" << v1.xCoordinate << ", " << v1.yCoordinate << ")" << std::endl;

	//v2.subtract(v3);
	//std::cout << "x and coordinates for v2: (" << v2.xCoordinate << ", " << v2.yCoordinate << ")" << std::endl;

	//system("pause");
	return 0;
}