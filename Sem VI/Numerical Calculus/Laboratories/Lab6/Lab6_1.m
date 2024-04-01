# 1)
# a)
xi = linspace(-2, 4 , 10);
fi = (xi + 1)./(3 .* xi.^2 + 2 .* xi + 1);

# b)
x = linspace(-2, 4, 500);
L9f = lagrange_int(xi, fi, x);
f = (x + 1)./(3 .* x.^2 + 2 .* x + 1);

plot(x, f, x, L9f, xi, fi, 'o');

# c)
plot(x, abs(f - L9f))
max(abs(f - L9f))

# d)
L9f_at_half = lagrange_int(xi, fi, 0.5);
f_at_half = (0.5 + 1)/(3 * 0.5^2 + 2 * 0.5 + 1);
abs(f_at_half - L9f_at_half)