# Solve the problem from the first set here


"""

Determine the `n-th` element of the sequence `1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,...` obtained from the sequence of
natural numbers by replacing composed numbers with their prime divisors, each divisor `d` being written `d` times,
without memorizing the elements of the sequence.

"""


import math  # required for determining the root of a number


def read():  # reads the input data
    x = int(input("Introduce a non-zero natural number: "))
    return x


def is_prime(x):  # verifies if x is prime
    if x < 2:
        return False
    for i in range(2, int(math.sqrt(x))+1):
        if x % i == 0:  # we found a divisor
            return False
    return True


def print_solution(x, n):
    if n == 1:
        print("The 1st element of the sequence is: " + str(x) + ".")
    elif n == 2:
        print("The 2nd element of the sequence is: " + str(x) + ".")
    elif n == 3:
        print("The 3rd element of the sequence is: " + str(x) + ".")
    else:
        print("The " + str(n) + "th element of the sequence is: " + str(x) + ".")


def prime_factorization(x, n, index):  # factorizes a composed number
    y = x  # create an auxiliary variable
    d = 2

    while d * d <= y and index < n:  # it's more efficient to check only the divisors that are smaller than sqrt(x)
        exp = 0  # initializes the exponent of the prime divisor d

        while y % d == 0:
            y //= d
            exp += 1

        if exp > 0:  # if d is a prime divisor of x
            index += d

        if index >= n:  # if d is the nth element of the sequence
            print_solution(d, n)

        d += 1

    if y > 1:  # the case where there is a prime divisor greater than sqrt(x) left
        if index < n:  # required for not printing the solution twice
            index += y
            if index >= n:
                print_solution(y, n)
    return index  # the value of index won't be affected


def solve(n):
    if n < 4:  # the first 3 values of the sequence coincide with their index
        print_solution(n, n)
    else:
        index = 3  # the index is incremented after computing
        element = 4  # first element to compute

        while index < n:
            if is_prime(element):
                index += 1
                if index == n:
                    print_solution(element, n)
            else:
                index = prime_factorization(element, n, index)

            element += 1


def main():
    n = read()
    solve(n)


# main function call
main()
