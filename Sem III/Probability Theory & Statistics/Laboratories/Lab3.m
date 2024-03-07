m = input('m = ')
s = input('s = ')
p1 = cdf('Normal', 0, m, s)

p2 = cdf('Normal', 1, m, s) - cdf('Normal', -1, m, s)
p3 = 1 - p2

a = input('a = ');
p4 = norminv(a, m, s);

b = input('b = ');
p5 = norminv(1-b, m, s);

a = input('a = ');
b = input('b = ');
option = input('distr = ', 's');
switch option
  case 'normal'
    m1 = input('m1 = ');
    s1 = input('s1 = ');
    p6 = cdf('Normal', 0, m1, s1);
    r6 = norminv(a, m1, s1);
    s6 = norminv(1-b, m1, s1);
  case 'student'
    m1 = input('m1 = ');
    p7 = cdf('t', 0, m1);
    r7 = tinv(a, m1);
    s7 = tinv(1-b, m1);
  case 'fischer'
    m1 = input('m = ');
    n1 = input('n = '); 
    p8 = cdf('f', 0, m1, n1);
    r8 = finv(a, m1, n1);
    s8 = finv(1-b, m1, n1);
  otherwise
    fprintf('Error');
endswitch

p = input('p = ');
n = input('n = ');
for n = 1:3:200
  k = 0:n;
  prob = binopdf(k, n, p);

  l = n.*p;
  p9 = pdf('Binomial', k, n, p);
  p10 = pdf('Poisson', k, l);

  xlim([0,200]);
  ylim([0,2]);
  pause(0.2);
end
plot(k, prob, k, p9, k, p10);