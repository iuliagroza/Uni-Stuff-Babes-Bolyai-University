for nodes = 1:5
  gaussquad(@(x)(x.^2 + 1)./(x.^2 + 1), nodes, 1)
endfor
integral(@(x)exp(cos(x)), 0, pi/4)