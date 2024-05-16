f = @(x)1./x;

log(2)
comp_rectangle(f, 1, 2, 18)
comp_trapezoid(f, 1, 2, 30)
simpsons(f, 1, 2, 18)