pkg load statistics

alpha = input("Significance level = ");
x = [3.26 1.89 2.42 2.03 3.07 2.95 1.39 3.06 2.46 3.35 1.56 1.79 1.76 3.82 2.42 2.96];
n = columns(x);

% a
m0 = 3;
[H, P, CI, stat] = ttest(x, m0, "alpha", alpha, "tail", "left");

if H == 0
	fprintf("The null hypothesis is not rejected. The particles seem to be larger than 3.\n")
else
	fprintf("The null hypothesis is rejected. The particles seem to be smaller than 3.\n")
end

q = tinv(alpha, n - 1);

fprintf("\nThe rejection region is [%6.4f, %6.4f].\n", -inf, q)
fprintf("The confidence interval is [%4.4f,%4.4f].\n", CI)
fprintf("The value of the test statistic is %6.4f.\n", stat.tstat)
fprintf("The P-value for the variances test is %6.4f.\n", P)

% b
confidence = input("Confidence interval = ");
alpha = 1-confidence;

xStdDev = std(x);

o1 = (n-1)*xStdDev*xStdDev/chi2inv(1-alpha/2, n-1);
o2 = (n-1)*xStdDev*xStdDev/chi2inv(alpha/2, n-1);

s1 = sqrt(o1);
s2 = sqrt(o2);

fprintf("The interval is [%f, %f].\n", s1, s2);
