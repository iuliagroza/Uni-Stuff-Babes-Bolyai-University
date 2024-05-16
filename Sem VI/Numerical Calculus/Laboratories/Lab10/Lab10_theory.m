# Rectangle (midpoint) formula

# Inta,b f(x) dx = h Si=0,(n-1)(f(a+i*h/2) + h^2(b-a)/24*f(eps)),
# eps from (a, b)

# Composite trapezoid
# fi = f(xi)
# f0 = a
# fn = b
# fi = f(a + ih)
# h*(f0 + f1)/2
# h*(f1 + f2)/2
# h(f(n-1) + fn)

# h/2(f(a) + f(b) + 2*(f1 + ... f(n-1))) - h^2(b-a)/12*f"(eps), eps from (a, b)

# Simpson's formula
# Inta,b f(x) dx = h/3*[f(a) + 4*Si=1,m(f(2i-1) + 2*Si=1,(m-1)(f2i + f(b)] +
# + 4^4(b-a)/180*f(4)(eps), eps from (a, b)