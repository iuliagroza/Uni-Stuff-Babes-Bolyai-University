function[z, td] = divdiff2(x, f, fd)
  n = length(x);
  z = zeros(1, 2*n);
  lz = 2*n;
  z = repelem(x, 2);
  td = zeros(lz);
  td(1:lz,1) = repelem(f,2)';
  td(1:2:lz-1, 2) = fd';
  td(2:2:lz-2, 2) = (diff(f)./diff(x))';
  for j = 3:lz
    td(1:lz-j+1, j) = diff(td(1:lz-j+2, j-1))./(z(j:lz) - z(1:lz-j+1))';
  endfor
end

# x = [-1, 1]
# f = [-3, 1]
# fd = [10, 2]
# [z, td] = divdiff2(x, f, fd)