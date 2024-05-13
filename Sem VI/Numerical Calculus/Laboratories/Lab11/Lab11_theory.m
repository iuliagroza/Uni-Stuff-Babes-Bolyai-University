# Romberg's Method
# (b - a) (f(a) + f(b))/2
# hk = (b-a)/2^k - length of subinterval

# R1,1 = h1/2*(f(a) + f(b))
# R2,1 = h2/2*(f(a) + f(b) + 2 * f(a + h2))
# ...
# Rk,1 = 1/2 * [R(k-1),1 + h(k-1)*Si=1,2^(k-2)(f(a + (i - 1/2)*h(k-1)), k = 2,n
# Rk,j = (4^(j-1) * Rk,(j-1) - R(k-1),(j-1))/(4^(j-1) - 1)

# |R(n-1),(n-1) - Rn,n| < eps - stopping condition

# Gaussian Quadrature
# Inta,b(w(x) * f(x)dx) = Sk=1,m(Ak * f(xk) + Rm(f))
# d = 2m-1 - degree of precision
# Jm(w) = [alpha0 sqrt(beta1) sqrt(beta2) ... 0]
#         [sqrt(beta1) alpha1 sqrt(beta2) ...]
#         [0  sqrt(beta2) alpha 2 ... 0]
#         [ ... ]
#         [0 ... sqrt(beta(m-1))]
#         [0 ... sqrt(beta(m-1)) alpha(m-1)]

# xk - eigenvalues
# Ak = beta0*wk,1^2, ||wk|| = 1
# wk1 - first component of the eigenvector
