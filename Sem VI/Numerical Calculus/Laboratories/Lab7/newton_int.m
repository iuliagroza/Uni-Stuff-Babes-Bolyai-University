function f = newton_int(xi, d, xx)
  for k = 1:length(xx)
    v = xx(k) - xi;
    f(k) = [1, cumprod(v(1:end-1))]*d(1,:)';
  endfor
  
  f
end