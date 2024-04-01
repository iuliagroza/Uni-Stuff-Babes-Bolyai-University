function f = lagrange_b(xi, fi, x)
  n = length(xi);
  w = ones(1,n);
  for j = 1:n
    w(j) = prod(xi(j) - xi([1:j-1,j+1:n]));
  endfor
  w = 1./w;
  numer = zeros(size(x));
  denom = numer;
  exact = numer;
  for j = 1:n
    xdiff = x - xi(j);
    term = w(j)./xdiff;
    numer = numer + fi(j)*term;
    denom = denom + term;
    exact(xdiff == 0) = j;
  endfor
  f = numer./denom;
  k = find(exact);
  f(k) = fi(exact(k));
end
