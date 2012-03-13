% Calculează recursiv valorile functiei f(m,n) definită astfel:
%   f(m,n) = n^m, daca n<m
%   f(m,n) = m*n, altfel

f(M,N,X)	:- N < M, fpow(N,M,X).
f(M,N,X)	:- X is M*N.

fpow(0,0,X)	:- X is 0.
fpow(0,_,X)	:- X is 1.
fpow(M,N,X)	:- P is M-1, fpow(P,N,Y), X is Y * N.
