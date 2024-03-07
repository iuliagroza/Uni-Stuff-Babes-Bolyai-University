A=[1,0,-2;2,1,3;0,1,0]
B=[2,1,1;1,0,-1;1,1,0]
C=A-B
fprintf('%d',C)
D=A*B
fprintf('%d',D)
E=A.*B
fprintf('%d',E)

plot(x,x.^5/10,x,x*sin(x),x,cos(x))
title('Plots')
legend('f1','f2','f3')
