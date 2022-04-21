# Testing the environment.
# Given a natural number n, calculate the sum of the first n natural numbers.

n = int(input())

s = 0

for i in range(n+1):  # calculate 1+2+...+n
    s += i

print(s)  # print the solution
