#include <stdio.h>
#include <assert.h>

typedef struct {
    int arr[5];
    int length;
} Vector;

/// <summary>
/// Example for passing by value.
/// </summary>
/// <param name="a">An integer.</param>
void byValue(int a) {
    a = a + 1;
    printf("Address of a in function: %p.\n", &a);
}

void byRefC(int *a) {
    *a = *a + 1;
}

void byRefCPointerByValue(int *x, int *y) {
    int *aux = x;
    x = y;
    y = aux;
}

void byRefCPP(int &a) {
    a = a + 1;
}

void passArray(int x[]) {
    x[0] = 1000; // <=> *x
    *(x + 3) = 4000; // <=> x[3]
}

void passStruct1(Vector v) {
    v.arr[0] = 1000;
}

void passStruct2(Vector *v) {
    v->arr[0] = 1000;
}

void testFunctionsForParameterPassing() {
    int a = 5;
    byValue(a);
    assert(a == 5);

    byRefC(&a);
    assert(a == 6);

    byRefCPP(a);
    assert(a == 7);
}

void functions() {
    int a = 10;
    printf("Address of a: %p.\n", &a);

    byValue(a);
    printf("Value remains unchanged: a = %d \n", a);

    byRefC(&a);
    printf("Value changed: a = %d \n", a);

    byRefCPP(a);
    printf("Value changed again: a = %d \n", a);

    a = 1;
    int b = 2;
    int *x = &a;
    int *y = &b;
    printf("Value pointed by x: %d, value pointed by y: %d.\n", *x, *y);
    byRefCPointerByValue(x, y);
    printf("Value pointed by x: %d, value pointed by y: %d.\n", *x, *y);

    int arr[5] = {1, 2, 3, 4, 5};    // arr is a pointer to the first element of the array arr
    passArray(arr);
    printf("arr[0] = %d, arr[3] = %d\n", arr[0], arr[3]);

    Vector v;
    v.arr[0] = 1;
    v.arr[1] = 2;
    v.length = 2;
    passStruct1(v);
    printf("v.arr[0] = %d\n", v.arr[0]);

    passStruct2(&v);
    printf("v.arr[0] = %d\n", v.arr[0]);

    testFunctionsForParameterPassing();
}

//int main() {
//    functions();
//    return 0;
//}