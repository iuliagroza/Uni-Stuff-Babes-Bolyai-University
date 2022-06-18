#include <stdio.h>

void statements() {
    int a = 2;

    ; // Empty statement, no effect

    if (a == 2) {
        printf("a has the value 2 and now we will modify it to 1.\n");
        a = 1;
    } // compound statement

    // conditional statement if, if-else, else if
    if (a == 2) {
        printf("a has the value 2.\n");
    } else if (a == 3) {
        printf("a has the value 3.\n");
    } else {
        printf("a is neither 2, nor 3.\n");
    }

    // conditional operator
    (a == 1) ? printf("a has the value 1.\n") : printf("a is not 1.\n");

    printf("Changing the value of a back to 2.\n");
    a = 2;

    // switch-case
    switch (a) {
        case 1:
            printf("a has the value 1.\n");
            break;
        case 2:
            printf("a has the value 2.\n");
            break;
        case 3:
            printf("a has the value 3.\n");
            break;
        default:
            break;
    }

    printf("\nWhile loop: \n");
    // while loop
    printf("Initialising a to 5.\n");
    a = 5;
    while (a < 5) {
        a++;
        printf("Increased a by 1. Now a is: %d.\n", a);
    }

    printf("\nInitialising a to 5.\n");
    a = 5;
    printf("Do-while loop: \n");
    // do-while loop
    do {
        a++;
        printf("Increased a by 1. Now a is: %d.\n", a);
    } while (a < 5);

    printf("\nFor loop: \n");
    // for loop
    for (a = 0; a < 5; a++) {
        printf("Increased a by 1. Now a is: %d.\n", a);
    }

    printf("\nFor loop - decreasing: \n");
    // for loop
    for (a = 4; a >= 0; a--) {
        printf("Decreased a by 1. Now a is: %d.\n", a);
    }
}

//int main() {
//    statements();
//    return 0;
//}