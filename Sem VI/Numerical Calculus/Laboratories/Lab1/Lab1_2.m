# Exercise 2
x = linspace(0, 2*pi, 100);
plot(x, sin(x), x, sin(2*x), x, sin(3*x));
clf;

# or
x = linspace(0, 2*pi, 100);
plot(x, sin(x));
hold on;
plot(x, sin(2*x));
hold on;
plot(x, sin(3*x));
clf;

# or
f = @(x) sin(x);
g = @(x) sin(2*x);
h = @(x) sin(3*x);
fplot(f, [0, 2*pi]);
hold on;
fplot(g, [0, 2*pi]);
hold on;
fplot(h, [0, 2*pi]);