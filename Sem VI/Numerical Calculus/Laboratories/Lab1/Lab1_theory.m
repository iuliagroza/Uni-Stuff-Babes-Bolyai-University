# Theory:
# A = [1 2; 3 4];
# A = [1 2]
#     [3 4]
# A^2 = A * A
# A.^2 = 2 * A
# size(A) = no. rows & no. cols
# B = [1 : 100] => B [1 2 ... 100]
# B = [1 : -0.1 : -100] => B = [1 0.9 ... -100] 
# diag(A) = [1 4] 
# => Create a matrix that only has elements only on the main diagonal
# If A is a vector, with A = [1 2 3 4], diag([1 2 3 4]) creates
# a matrix B = [1 0; 0 4] 
t = linspace(0, 10*pi, 1000);
R = 3.8;
r = 1;
x = (R + r) * cos(t) - r*cos((R/r + 1)*t);
y = (R + r) * sin(t) - r*cos((R/r + 1)*t);
plot(x, y);