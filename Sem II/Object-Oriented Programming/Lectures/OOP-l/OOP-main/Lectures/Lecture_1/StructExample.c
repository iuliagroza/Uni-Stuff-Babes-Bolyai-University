#include <stdio.h>

// use typedef to introduce a new type integer
typedef int integer;

//introduce a new type called Car
typedef struct {
    int year;
    integer km;
} Car;

void structExample() {
    Car car1, car2;
    //initialise fields
    car1.year = 2012;
    car1.km = 20000;
    printf("Car 1 fabrication year: %d, Km: %d \n", car1.year, car1.km);

    //!!! car2 fields are uninitialised => crash
    //printf("Car 2 fabrication year: %d, Km: %d \n", car2.year, car2.km);

    // initialize car2
    car2 = car1;
    printf("Car 2 fabrication year: %d, Km: %d \n", car2.year, car2.km);
}

//int main() {
//    structExample();
//    return 0;
//}