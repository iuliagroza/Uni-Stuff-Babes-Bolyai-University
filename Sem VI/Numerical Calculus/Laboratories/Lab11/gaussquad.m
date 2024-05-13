function [I, g_nodes, g_coeff] = gaussquad(f, n, g_type)
  alpha_vec = zeros(n,1);
  switch g_type
    case 1 # Legendre
      beta_vec = [2, (4 - ([1:n-1].^(-2)).^(-1))];
    case 2 # Chebyshev 1st
      beta_vec = [pi, 0.5, ones(2, n-1)*0.25];
    case 3 # Chebyshev 2nd
      beta_vec = [pi/2, ones(1, n-1)*0.25];
  case 4 # Laguerre
      alpha_vec = [1:n-1].*2 + 1;
      beta_vec = [gamma(1), [1:n-1].^2];
    case 5 # Hermite
      beta_vec = [sqrt(pi), [1:n-1]*0.5];
  endswitch
  
  J = diag(alpha_vec) + diag(sqrt(beta_vec(2:n)), -1) + diag(sqrt(beta_vec(2:n)), 1);
  [v, d] = eig(J);
  g_nodes = diag(d);
  g_coeff = beta_vec(1)*v(1,:).^2;
  I = g_coeff*f(g_nodes);
end