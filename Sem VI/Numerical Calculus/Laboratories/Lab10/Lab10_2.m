f = @(x)sqrt(1 + (pi*cos(pi*x)).^2);
a = 0;
b = 1;
err = 10^(-3);
m = 4;
method = @simpsons;

adquad(f, a, b, err, method, m)