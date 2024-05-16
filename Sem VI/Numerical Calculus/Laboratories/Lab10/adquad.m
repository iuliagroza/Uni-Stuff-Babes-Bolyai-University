function I = adquad(f, a, b, err, method, m)
  I1 = method(f, a, b, m);
  I2 = method(f, a, b, 2*m);
  if abs(I1 - I2) < err
    I = I2;
    return;
  else
    I = adquad(f, a, (a+b)/2, err, method, m) + adquad(f, (a+b)/2, b, err, method, m);
  endif
end