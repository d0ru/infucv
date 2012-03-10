% Calculează funcția lui Fibonacci într-un punct dat.
%   f(1) = f(2) = 1
%   f(n) = f(n-1) + f(n-2), pentru n > 2

f(1,1).
f(2,1).
f(N,X)	:- N > 2, N1 is N-1, N2 is N-2, f(N1,X1), f(N2,X2), X is X1+X2.
