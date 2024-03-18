function x = forw_sub(L, b)
  n = length(b);
  x = zeros(size(b));
  for i = 1 : n
    x(i) = (b(i) - L(i,1:i-1)*x(1:i-1))/L(i,i);
  endfor
end
