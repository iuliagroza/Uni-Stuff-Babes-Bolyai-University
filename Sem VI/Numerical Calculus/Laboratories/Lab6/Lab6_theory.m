# Lagrange Interpolation

# u(x) = (x-1)(x-2)(x-3)

# x0, x1, ..., xn - nodes
# f(x0), f(x1), ..., f(xn) - given
# u(x) = (x-x0)*(x-x1)*...*(x-xn) = Pi=0,n(x-xi)
# uj(x) = Pi-0,n(x-xi)/(x-xj) = (x-x0)*(x-x1)*...*
# *((x-x(j-1))*(x-x(j+1))*...*(x-xn)
# lj(x) = uj(x)/uj(xj) = uj(x)/u'(xj)
# Lnf(x) = Si=0,nf(xi)*li(x), li(x) - basis

# Barycentric form

# Lnf(x) = Si=0,nf(xi)*li(x) = Si=0,nf(xi)*ui(x)/u'(xi) = 
# = Si=0,nf(xi)*u(x)/((x-xi)u'(xi))) = u(x)*Si=0,nf(xi)*
# * 1/(u'(xi)*(x-xi)) = u(x) Si-0,nf(xi)*(1/u'(xi))/(x-xi)
# wi = 1/((x-x0)*...(xix(i-1))*(x-x(i+1))*...*(x-xn)) - weight
# Lnf(x) = u(x)*Si=0,nf(xi)*wi/(x-xi)
# u(x) * Si=0,nwi/(x-xi) = 1 (Geometric interpetation)
# => u(x) = 1/(Si=0,nwi/(x-xi))
# => Lnf(x) = Si-0,n(f(xi)*wi/(x-xi))/(Si=0,n(wi/(x-xi))