A = [2, 1, -1, -2; 4, 4, 1, 3; -6, -1, 10, 10; -2, 1, 8, 4]
b = [2; 4; -5; 1]

[L, U, P] = lu(A);

y = forw_sub(L, P*b)
x = back_sub(U, y)

gauss_elim(A, b)