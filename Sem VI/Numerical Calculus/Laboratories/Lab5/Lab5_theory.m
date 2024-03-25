# 9x1 + x2 + x3 = b1
# 2x1 + 10x2 + 3x3 = b2
# 3x1 + 4x2 + 11x3 = b3

# x1 = 1/9(b1 - x2 - x3)
# x2 = 1/10(b2 - 2x1 - 3x3)
# x3 = 1/11(b3 - 3x1 - 4x2)

# x^0 = (X1^0, x2^0, x3^0) - guess
# x1^(k+1) = 1/9(b1 - x2^k - x3^k)
# x2^(k+1) = ...
# x3^(k+1) = ...

# Jacobi
# Ax = b
# A = D - L - U
# D =  (a11 ... 0, ..., 0 ... ann)
# -L = (0 ... 0, a21 ... 0, ..., an1 ... ann)
# -U = (0 a12 ... a1n, ..., 0 ... a(n-1)n, 0 ... 0)
# M = D, N = L + U
# T = D^(-1)(L + U) = M^(-1)N, C = D^(-1)b = M^(-1)b
# X^(k+1) = T*x^k + c, stopping condition: 
# ||x^k - x^(k-1)|| <= (1 - ||T||)/||T||*eps, eps - given

# Gauss-Siedel