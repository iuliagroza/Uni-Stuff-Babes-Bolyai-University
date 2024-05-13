# Int0,pi/2(dx/(2 + sinx)) = pi*sqrt(3)/9

[I, nfev] = romberg(@(x)1./(2 + sin(x)), 0, pi/2, 10^(-6), 25)
pi*sqrt(3)/9
abs(I - pi*sqrt(3)/9)