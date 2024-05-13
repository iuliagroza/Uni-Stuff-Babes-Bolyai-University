function [I, nfev] = romberg(f, a, b, eps, nmax)
  R = zeros(nmax);
  h = b - a;
  R(1,1) = h/2*sum(f([a, b]));
  nfev = 2;
  for k = 2:nmax
    x = a + (1:2^(k-2) - 0.5) * h;
    R(k,1) = 0.5*(R(k-1, 1) + h*sum(f(x)));
    nfev = nfev + length(x);
    for j = 2:k
      R(k,j) = (4^(j-1)*R(k, j-1) - R(k-1, j-1))/(4^(j-1) - 1);
    endfor
    if abs(R(k-1,k-1) - R(k,k)) < eps
      I = R(k,k);
      R(1:k,1:k)
      return
    endif
    h = h/2;
  endfor
  error('Iteration number exceeded');
 end
