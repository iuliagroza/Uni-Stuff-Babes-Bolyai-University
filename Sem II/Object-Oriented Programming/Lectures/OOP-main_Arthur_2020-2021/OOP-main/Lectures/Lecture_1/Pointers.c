#include <stdio.h>

void pointers() {
    int a = 7;
    printf("value of a: %d, address of a: %p \n", a, &a);

    //assign the address of a to pa
    int *pa;
    pa = &a;
    printf("value of pa: %p, address of pa: %p \n", pa, &pa);

    // pa refers to the address of a => if a changes, *pa also changes
    a = 10;
    printf("value of a: %d, dereference of pa: %d \n", a, *pa);

    *pa = 20;
    printf("%d", a);
}

//int main() {
//    pointers();
//    return 0;
//}