xi = -2:4;
xx=linspace(-2,4);
fi = (xi+1)./(3*xi.^2+2*xi+1);
f = (xx+1)./(3*xx.^2+2*xx+1);
dfi = -(3*xi.^2+6*xi+1)./(3*xi.^2+2*xi+1).^2;
plot(xx,f);
hold on;
d=divided_diff(xi,fi);
plot(xx,newton_int(xi,d,xx));

[zi,d2]=divided_diff2(xi,fi,dfi);
plot(xx,newton_int(zi,d2,xx));

S=spline(xi,fi,xx);
plot(xx,S)
