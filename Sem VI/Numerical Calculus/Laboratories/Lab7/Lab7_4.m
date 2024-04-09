xi = [39 : 51 : 2];
fi = [0.6293204, 0.6560590, 0.6819984, 0.7071068, 0.7313597, 0.7547096, 0.7771460];
xx = [40, 44, 50];

dd = divdiff(xi, fi);
newton_int(xi, dd, xx)

d = fordiff(fi);
newton_int(xi, dd, xx)
