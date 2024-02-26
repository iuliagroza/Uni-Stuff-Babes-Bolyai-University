# Exercise 1
# a)
p = [1, -5, -16, 16, -17, 21];
x = [-4 : .1 : 7.2];
px = polyval(p, x);
plot(x, px);

# b)
v = polyval(p, -2.5);

# c)
roots(p);
