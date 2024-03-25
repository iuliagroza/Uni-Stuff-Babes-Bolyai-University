function [x, nit] = jacobi_iteration(A, b, x0, maxit, epsilon)
  M = diag(diag(A));
  N = M - A;
  T = inv(M)*N;
  c = inv(M)*b;
  alpha = norm(T, inf)
  for nit = 1 : maxit
    x = T * x0 + c;
    if norm(x - x0, inf) <= epsilon * (1 - alpha)/alpha
      return
    endif
    x0 = x;
  endfor
end