x = 0:.1:3
plot(x, x.^5/10, '--r', x, x.*sin(x), '+k', x, cos(x), 'oc')
title('Plots')
legend('f1', 'f2', 'f3')

subplot(3, 1, 1) : plot(x, x.^5/10, '--r')
subplot(3, 1, 2) : plot(x, x.*sin(x), '+k')
subplot(3, 1, 3) : plot(x, cos(x), 'oc')