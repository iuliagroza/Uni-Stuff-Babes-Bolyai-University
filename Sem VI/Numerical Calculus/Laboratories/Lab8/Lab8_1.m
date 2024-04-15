# 1
xi = [0, 1, 2];
fi = 1./(1 + xi);
xx = linspace(0, 2, 100);
d = divdiff(xi, fi);
Lf = newton_int(xi, d, xx);
plot(xx, Lf)

# H3f(x) = f(a) + f[a, a]*(x - a) + f[a, a, b]*(x - a)^2 + 
# + f[a, a, b, b]*(x - a)^2*(x - b);
dfi = -1./(1+xi).^2;
[zi, d2] = divdiff2(xi, fi, dfi);
Hf = newton_int(zi, d2, xx);

hold on;
plot(xx, Hf);