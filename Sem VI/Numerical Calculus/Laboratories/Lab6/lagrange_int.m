function f = lagrange_int(xi, fi, x)
  f  = zeros(size(x));
  n = length(xi);
  for i = 1 : n
    z = ones(size(x));
    for j=[1:i-1,i+1:n]
      z = z .* (x - xi(j))/(xi(i) - xi(j));
    endfor
    
    f = f + fi(i) * z;
  endfor
end
