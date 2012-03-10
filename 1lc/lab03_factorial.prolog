% Calculează factorialul unui număr natural «n».
%   factorial(x) = 1, dacă x=0
%   factorial(x) = fact(x-1)*x, altfel

% n*(n-1)*..2*1
factorial(0,1).
factorial(N,F)	:- N1 is N-1, factorial(N1,F1), F is N*F1.

factorial(N)	:- fact3(N,1,F), write('Factorialul numărului «'), write(N), write('» este '), write(F), writeln('.').
% -N numărul natural curent
% +P produsul parțial n*(n-1)*..*N
% +F rezultatul final al funcției
fact3(0,F,F).
fact3(N,P,F)	:- N1 is N-1, P1 is N*P, fact3(N1,P1,F).
