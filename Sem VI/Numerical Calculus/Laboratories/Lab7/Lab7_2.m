xi = linspace(-4, 4, 9);
fi = 2 .^ xi; 
xx = 1/2;

aitken(xi, fi, xx)

d = divdiff(xi, fi);
newton_int(xi, d, xx)