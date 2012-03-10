% Calculează pentru «n» dat valoarea elementului Xn din șirul:
%   Xn = ∑(1/i), i=1..n

sir_Xn(1,1).
sir_Xn(N,X)	:- N > 1, N1 is N-1, sir_Xn(N1,Y), X is Y+(1/N).
