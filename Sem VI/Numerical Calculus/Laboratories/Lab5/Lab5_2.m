A = [10, 7, 8, 7; 7, 5, 6, 5; 8, 6, 10, 9; 7, 5, 9, 10];
Ai = [10, 7, 8.1, 7.2; 7.8, 5.04, 6, 5; 8, 5.98, 9.89, 9; 6.99, 4.99, 9, 9.98];
b = [32; 23; 33; 31];
bi = [32.1; 22.9; 33.1; 30.9];

# a)
sola = inv(A)*b

# b)
solb = inv(A)*bi
err_in = norm(bi - b)/norm(b)
err_out = norm(solb - sola)/norm(sola)

# c)
solc = inv(Ai)*b
err_in = norm(Ai - A)/norm(A)
err_out = norm(solc - sola)/norm(sola)

cond(A)