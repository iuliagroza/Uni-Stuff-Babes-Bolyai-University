# 2
xi = [0, 3, 5, 8, 13]; # time
fi = [0, 225, 383, 623, 993]; # distance
dfi = [0, 77, 80, 74, 72]; # velocity

x = 10;
[zi, d2] = divdiff2(xi, fi, dfi);
pos = newton_int(zi, d2, x)

d = divdiff(xi, dfi);
newton_int(xi, d, x)

d3 = divdiff(fi, dfi);
newton_int(fi, d3, pos)