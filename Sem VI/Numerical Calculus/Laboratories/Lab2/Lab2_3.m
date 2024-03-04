# 3 a) ln(1 + x), degree 2, 5, x from [-0.9, 1] 
pkg load symbolic
syms x # defines x as a symbol

f = log(1 + x)
Tf1 = taylor(f, x, 0, 'Order', 2)
Tf2 = taylor(f, x, 0, 'Order', 5)

ezplot(f, [-0.9, 1])
hold on
ezplot(Tf1, [-0.9, 1])
hold on
ezplot(Tf2, [-0.9, 1])

# b)
Tf = taylor(f, x, 0, 'Order', 200000)
a = subs(Tf, x, 1);
vpa(a, 5)

# c)
f1 = log(1 + x)
Tf1 = taylor(f, x, 0, 'Order', 7)
f2 = log(1 - x)
Tf2 = taylor(f, x, 0, 'Order', 7)

ezplot(Tf1, [-0.9, 1])
hold on
ezplot(Tf2, [-0.9, 1])

# d)
# ln((1+x)/(1-x)) = ln(1+x) - ln(1-x)
Tf = taylor(f1-f2, x, 0, 'Order', 7)
ezplot(Tf, [-0.9, 1])

# e)
# ln2 = ln((1+x)/(1-x)) => x = 1/3
Tf = taylor(f1-f2, x, 0, 'Order', 8)
a = subs(Tf, x, 1/3);
vpa(a, 5)

# Approximation of 5 decimals at deg. 8
