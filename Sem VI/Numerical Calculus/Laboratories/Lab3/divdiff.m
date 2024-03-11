# Divided differences divdif m.

function td = divdiff(x, f)  
  n = length(x);
  td = zeros(n);
  td(:,1) = f';
  for j = 2:n
    td(1:n-j+1, j) = diff(td(1:n-j+2, j-1))./(x(j:n) - x(1:n-j+1))';
  endfor
end

# x = [0, 1/6, 1/2]
# f = [0, 1/2, 1]
# divdiff(x, f)