function Lab1_5
  f_2 = f(2);
  f_10 = f(10);
  f_2024 = f_iterative(2024);

  # Output the results
  disp(['f(2) = ', num2str(f_2)]);
  disp(['f(10) = ', num2str(f_10)]);
  disp(['f(2024) = ', num2str(f_2024)]);
endfunction

# Local function definitions
# Recursive solution
function result = f(n)
  if n == 1
      result = 1.5;
  else
      result = 1 + 1 / f(n - 1);
  endif
endfunction

# Iterative solution (to avoid stack overflow)
function result = f_iterative(n)
  result = 1.0;
  for i = 1:n
      result = 1 + 1 / result;
  endfor
endfunction
