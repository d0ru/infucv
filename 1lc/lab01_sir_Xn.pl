% Calculează pentru 'n' dat valoarea elementului Xn din șirul:
%   Xn=suma(1/i) cu i=1..n

sir_Xn(0,X)	:- X is 0.
sir_Xn(1,X)	:- X is 1.
sir_Xn(N,X)	:- M is N-1, sir_Xn(M,Y), X is Y+(1/N).
