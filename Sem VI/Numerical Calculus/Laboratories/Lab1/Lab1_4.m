# Exercise 4
[x, y] = meshgrid(linspace(-2, 2, 100), linspace(0.5, 4.5, 100));
f = sin(exp(x)).*cos(log(y));
mesh(x, y, f);
clf;
plot3(x, y, f);