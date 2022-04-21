# Solve the problem from the second set here


"""

8. Find the smallest number `m` from the Fibonacci sequence, defined by `f[0]=f[1]=1`, `f[n]=f[n-1] + f[n-2]`, for `
n > 2`, larger than the given natural number `n`. (e.g. `for n = 6, m = 8`).

"""


def read():  # reads the input data
    x = int(input("Introduce a natural number greater than 2: "))
    return x


def solve(x):
    f0 = 1  # f[0] = 1
    f1 = 1  # f[1] = 1
    f2 = f0 + f1

    while f2 <= x:
        f0 = f1
        f1 = f2
        f2 = f0 + f1  # f[n] = f[n-1] + f[n-2]

    return f2  # the smallest number from the Fibonacci sequence larger than x


def main():
    n = read()

    solution = solve(n)

    print("The smallest Fibonacci sequence term larger than " + str(n) + " is: " + str(solution) + ".")


# main function call
main()
