# 1 a) plot e^x and its Taylor polyonmials of degree 1, 2, 3, and 4, x from [-3, 3].
pkg load symbolic
syms x # defines x as a symbol

f = exp(x)
Tf1 = taylor(f, x, 0, 'Order', 2)
Tf2 = taylor(f, x, 0, 'Order', 3)
Tf3 = taylor(f, x, 0, 'Order', 4)
Tf4 = taylor(f, x, 0, 'Order', 5)

ezplot(Tf1, [-3, 3])
hold on
ezplot(Tf2, [-3, 3])
hold on
ezplot(Tf3, [-3, 3])
hold on
ezplot(Tf4, [-3, 3])

# b)
# e
# vpa(e, 7)

# exp(1)
# vpa(exp(1), 7)

# a = subs(Tf4, x, 1)
# vpa(a, 7)

n = 30
for i = 2:n
    Tf = taylor(f, x, 0, 'Order', i);
    a = subs(Tf, x, 1); i
    vpa(a, 7)
end

# Approximation of 6 decimals at deg. 11