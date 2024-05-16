function I = comp_trapezoid(f, a, b, n)
  h = (b-a)/n;
  I = h/2*(f(a) + f(b) + 2*sum(f([1:n-1]*h + a)));
end