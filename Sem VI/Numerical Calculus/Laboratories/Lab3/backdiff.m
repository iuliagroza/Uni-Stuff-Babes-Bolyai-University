# Backward differences

function td = backdiff(f)
  n = length(f);
  td = zeros(n);
  td(:, 1) = f';
  for j = 2:n
    td(j:n, j) = diff(td(j-1:n, j-1));
  endfor
end
  