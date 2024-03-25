n = 1000
[A, b] = square_matrix(n);
x0 = zeros(size(b));
maxit = 1000;
epsilon = 10^(-5);

[x, nit] = jacobi_iteration(A, b, x0, maxit, epsilon);

[x, nit] = gauss_siedel_iteration(A, b, x0, maxit, epsilon);

x
nit
