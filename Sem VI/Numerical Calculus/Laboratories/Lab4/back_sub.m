function x = back_sub(U, b)
  n = length(b);
  x = zeros(size(b));
  for i = n : -1 : 1
    x(i) = (b(i) - U(i, i+1:n)*x(i+1:n))/U(i,i);
  endfor
end

