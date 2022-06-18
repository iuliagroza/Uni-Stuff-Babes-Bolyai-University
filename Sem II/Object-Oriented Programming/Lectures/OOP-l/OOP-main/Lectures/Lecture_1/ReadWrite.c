#include <stdio.h>

int readWrite() {
    int nr = 5;
    double nrf = 3.14;
    char c = 's';
    char str[] = "abc";
    printf("%d %lf %c %s\n", nr, nrf, c, str);

    printf("Input a new value for nrf: ");
    scanf("%lf", &nrf); // read a double
    printf("nrf is now %.2f.\n", nrf);

    char name[10];
    int age = 0;
    printf("Input a name and an age: ");
    scanf("%s %d", name, &age);
    printf("Name: %s, age: %d.\n", name, age);
}

//int main() {
//    readWrite();
//    return 0;
//}