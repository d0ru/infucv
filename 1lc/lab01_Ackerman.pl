% Calculează valorile funcției lui Ackerman
%   ac: NxN -> N
%   ackerman(m,n) = n + 1, dacă m=0
%   ackerman(m,n) = ackerman(m-1, 1), dacă n=0
%   ackerman(m,n) = ackerman(m-1, ackerman(m,n-1)), altfel

ackerman(0,N,X)	:- X is N+1.
ackerman(M,0,X)	:- P is M-1, ackerman(P,1,X).
ackerman(M,N,X)	:- P is M-1, Q is N-1, ackerman(M,Q,R), ackerman(P,R,X).
