# Solve the problem from the first set here


# 2. Given natural number n, determine the prime numbers p1 and p2 such that n = p1 + p2 (check the Goldbach hypothesis)


import math  # # required for determining the root of a number


def read():  # reads the input data
    x = int(input("Introduce a natural number greater than 3: "))
    return x


def is_prime(x):  # verifies if x is prime
    if x < 2:
        return False
    for i in range(2, int(math.sqrt(x))+1):
        if x % i == 0:  # we found a divisor
            return False
    return True


def print_error():
    print("There is no solution for this input.")


def solve(x):
    ok = False

    for i in range(2, x - 1):
        if is_prime(i) and is_prime(x - i):
            print("The solution is: (" + str(i) + ", " + str(x - i) + ").")
            ok = True
            break

    if not ok:
        print_error()  # the case where n is odd and n-2 is not prime is not valid


def main():
    n = read()
    if n < 4:  # Goldbach's conjecture is not valid for numbers smaller than 4
        print_error()
    else:
        solve(n)


# main function call
main()
