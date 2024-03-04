# 2 a) sin x, degree 3, 5 x from [-pi, pi].
pkg load symbolic
syms x # defines x as a symbol

f = sin(x)
Tf1 = taylor(f, x, 0, 'Order', 3)
Tf2 = taylor(f, x, 0, 'Order', 5)

ezplot(f, [-pi, pi])
hold on
ezplot(Tf1, [-pi, pi])
hold on
ezplot(Tf2, [-pi, pi])

# b)
n = 30
for i = 2:n
    Tf = taylor(f, x, 0, 'Order', i);
    a = subs(Tf, x, pi/5); i
    vpa(a, 5)
end

# Approximation of 5 decimals at deg. 6

# c)
# sin(10pi/3) = sin(2pi * 4pi/3) = sin(4pi/3) 
# = sin(pi + pi/3) = - sin(pi/3) = sin(-pi/3)

# We can compute it for x = -pi/3 for a faster approximation
# instead of x = 10pi/3

n = 30
for i = 2:n
    Tf = taylor(f, x, 0, 'Order', i);
    a = subs(Tf, x, -pi/3); i
    vpa(a, 5)
end

# Approximation for 10pi/3 at deg. 36
# Approximation for 4pi/3 at deg. 16
# Approximation for -pi/3 at deg. 8