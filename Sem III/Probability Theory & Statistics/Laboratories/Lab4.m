% Bernoulli Distribution
clear X
p = input('p = ');
N = input('N = ');

for i=1:N
  r = rand;
  X(i) = r < p;
end

U_X = unique(X);
n_x = hist(X, length(U_X));
n_x/N;

% Binomial Distrbution
clear X
p = input('p = ');
N = input('N = ');
n = input('n = ');

for i=1:N
  r = rand(n, N);
  X = sum(r < p);
end

U_X = unique(X);
n_x = hist(X, length(U_X));
k = 0:n;
p_k = pdf('Bino', k, n, p);
clf
plot(k, p_k, 'o', U_X, n_x/N, '*');

% Geometric Distribution
clear X
p = input('p = ');
N = input('N = ');

for i=1:N
  X(i) = 0;
  while rand >= p
    X(i) = X(i) + 1;
  endwhile
end

U_X = unique(X);
n_x = hist(X, length(U_X));
k = 0:20;
p_k = pdf('Geo', k, p);
clf
plot(k, p_k, 'o', U_X, n_x/N, '*'); 

% Pascal Distribution
clear X
p = input('p = ');
N = input('N = ');
n = input('n = ');

for i=1:N
  r = rand(n, N);
  X = sum(r < p);
end

U_X = unique(X);
n_x = hist(X, length(U_X));
k = 0:n;
p_k = nbinpdf(k, n, p);
clf
plot(k, p_k, 'o', U_X, n_x/N, '*');
