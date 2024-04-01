# 2
xi = 1980 : 10: 2020;
fi = [4451 5287 6090 6970 7821];
x = [2005, 2015];
est_y = lagrange_b(xi, fi, x);

actual_y = [6474 7405];
abs(actual_y - est_y)