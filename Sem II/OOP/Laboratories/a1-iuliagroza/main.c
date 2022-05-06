#include <stdio.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define nMAX 10005


typedef struct {
    /*Struct used to retain an array structure (its length and elements). It eases the process of passing function
     parameters by reference*/
    int arr[nMAX];
    int len;
} vector;


/* UI section */
void print_menu() {
    /*Function that prints the main menu.*/
    printf("Welcome! Choose one of the following commands by typing its corresponding number: \n"
           "1. Print the Pascal's Triangle of dimension n of all combinations C(m,k) of m objects taken by k, k = 0, 1, ..., m, for line m, where m = 1, 2, ..., n. \n"
           "2. Read an array of numbers and find its longest contiguous subsequence of prime numbers. \n"
           "3. Compute the approximated value of square root of a positive real number. The precision is provided by the user. \n"
           "4. Exit \n");
}


int get_menu_input() {
    /*Function that returns the input for the main menu of the console application.
      return: int (1, 2, 3 or 4)*/
    printf(">>> ");

    int option = 0;
    scanf("%d", &option);

    return option;
}


int get_first_feature_input() {
    /*Function that gets the input of the first functionality (the dimension of the Pascal's) and returns it.
      return: int (non-zero natural number)*/
    printf("Please enter the dimension of the Pascal's Triangle (non-zero natural number): \n"
           ">>> ");

    int n = 0;
    scanf("%d", &n);

    return n;
}


void print_first_feature_solution(long long n) {
    printf("%lld ", n);
}


void print_newline() {
    printf("\n");
}


vector get_second_feature_input() {
    /*Function that gets the input of the second functionality (a non-zero natural number n and n integers) and then
      returns a vector struct element v, where v.len = n and v.arr contains the n integers.
      return: vector*/
    printf("Please enter the number of elements the read vector will contain: \n"
           ">>> ");

    vector v;
    scanf("%d", &v.len);

    printf("Please enter the elements separated by whitespaces: \n"
           ">>> ");
    for (int i = 0; i < v.len; i++) {
        scanf("%d", &v.arr[i]);
    }

    return v;
}


void print_second_feature_solution(vector v) {
    /*Function that prints the solution of the second feature.*/
    if (v.len == 0) {
        printf("There are no prime numbers in the provided array. \n");
    } else {
        printf("The longest contiguous subsequence of prime numbers is: \n");
        for (int i = 0; i < v.len; i++) {
            printf("%d ", v.arr[i]);
        }
        printf("\n");
    }
}


double get_third_feature_input() {
    /*Function that returns the number we want to compute the square root of.
      return: double*/
    double x;

    printf("Enter a positive real number: ");
    scanf("%lf", &x);

    return x;
}

int get_precision() {
    /*Function that returns the precision specified by the user.
      return: unsigned long long*/
    unsigned long long precision;

    printf("Provide the precision: ");
    scanf("%lld", &precision);

    return precision;
}

void print_third_feature_solution(double x, double x_root, unsigned long long precision) {
    /*Function that prints the square root of a number "x" with a precision "precision"
      :x: double
      :x_root: double
      :precision: unsigned long long*/
    double solution = floor(precision*x_root)/precision;
    printf("The square root of %lf is %lf\n", x, solution);
}


/* Non-UI section */
void solve_first_feature(int n) {
    /*Function that solves the first feature. We know that C(m, k) = m!/(m-k)!*k! for any m and k<=m, so
      C(m, k) = C(m, k-1)*(m-k+1)/k. Time-Complexity: O(n^2)*/
    for (int i = 1; i <= n; i++) {
        long long C = 1;
        for (int j = 1; j <= i; j++) {
            print_first_feature_solution(C);
            C = C * (i - j) / j;
        }
        print_newline();
    }
}


void first_feature() {
    /*First feature main function.*/
    int n = get_first_feature_input();
    solve_first_feature(n);
}


int check_primality(int n) {
    /*Classic function that checks the primality of a natural number. If n is less than 2, it is not prime. Otherwise,
      we check if n has any proper divisors. Note: it is sufficient to check only the divisors up to sqrt(n) included,
      not n-1 (optimization). Time Complexity: O(sqrt(n))
      return: bool (1 if n is prime,
                    0 otherwise)
      */
    if (n < 2) {
        return FALSE;
    }

    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return FALSE;
        }
    }

    return TRUE;
}


vector solve_second_feature(vector v) {
    /*Function that solves the second feature using the Sliding Window (2p) technique. We start with two "pointers"
      initialized with -1. If we find a prime number and right is -1 (we are currently not in a prime numbers contiguous
      sequence), then we initialize the sequence. Otherwise, we increase the length of the sequence (we increase right,
      so length = right - left + 1 implicitly increases). We constantly update the solution. Time Complexity: O(v.len)
      return: vector*/
    int i = 0, left = -1, right = -1, Max = 0, Max_left = 0, Max_right = 0;
    while (i < v.len) {
        if (check_primality(v.arr[i])) {
            if (right == -1) {
                left = i;
                right = left;
            } else {
                right++;
            }

            if (right - left + 1 > Max) {
                Max = right - left + 1;
                Max_left = left;
                Max_right = right;
            }
        } else {
            right = -1;
        }
        i++;
    }

    vector ans;
    ans.len = Max;
    for (int ind = 0; ind < ans.len; ind++) {
        ans.arr[ind] = v.arr[Max_left + ind];
    }

    return ans;
}


void second_feature() {
    /*Second feature main function.*/
    vector v = get_second_feature_input();
    vector ans = solve_second_feature(v);
    print_second_feature_solution(ans);
}


void third_feature() {
    /* Third feature main function. */
    double x = get_third_feature_input();
    unsigned long long precision = get_precision();
    double x_root = sqrt(x);
    print_third_feature_solution(x, x_root, pow(10, precision));
}


/* Main function */
int main() {
    while (TRUE) {
        print_menu();

        int option = get_menu_input();
        if(option == 1) {
            first_feature();
        } else if (option == 2) {
            second_feature();
        } else if (option == 3) {
            third_feature();
        } else {
            break;
        }
    }
    return 0;
}