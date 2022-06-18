#include "vector_v1/Vector2D.h"
#include <iostream>

#define PI 3.14159265

#include <cmath>

using namespace VectorOne;

void vector2d_example_1() {
    Vector2D v1{1, 1};    // aggregate initialization
    Vector2D v2;            // uninitialised: x and y coordinates contain garbage!
    v2.xCoordinate = 2;
    v2.yCoordinate = 3;

    Vector2D v3{}; // x and y coordinates are initialised with default values for their types (0 - for doubles)

    v1.add(v2);
    std::cout << "x and y coordinates for v1: (" << v1.xCoordinate << ", " << v1.yCoordinate << ")" << std::endl;

    v1.rotate(PI / 3);
    std::cout << "x and y coordinates for v1: (" << v1.xCoordinate << ", " << v1.yCoordinate << ")" << std::endl;

    v2.subtract(v3);
    std::cout << "x and y coordinates for v2: (" << v2.xCoordinate << ", " << v2.yCoordinate << ")" << std::endl;
}

//int main() {
//    vector2d_example_1();
//}