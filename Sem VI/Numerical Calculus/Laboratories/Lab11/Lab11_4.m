for nodes=2:8:2
  # a
  gaussquad(@(x)(x.^2 + 1)./(x.^2 + 1), nodes, 5)
  integral(@(x)e.^(-x).*sin(x), 0, inf)

  # b
  gaussquad(@(x)(x.^2 + 1)./(x.^2 + 1), nodes, 5)
  integral(@(x)e.^((-x).^2).*cos(x), -inf, inf)

  # c
  gaussquad(@(x)(x.^2 + 1)./(x.^2 + 1), nodes, 3)
  integral(@(x)sin(x.^2)./sqrt(1-x.^2), -1, 1)
endfor