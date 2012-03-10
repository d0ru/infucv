% Să se verifice dacă un număr «k» este divizor al unui număr «n». Construiți
% apoi un predicat Prolog care să afișeze toți divizorii unui număr natural «n».

divide(0,_)	:- writeln('Impartirea la 0 nu este permisa').
divide(K,N)	:- P is N mod K, P == 0.
nu_divide(K,N)	:- P is N mod K, P =/= 0.

% D - numărul de pornire, incrementat atât timp cât N > D
divizori(N)	:- write('Divizorii lui «'), write(N), write('» sunt:'), divN(N,2), writeln('.').
divN(1,_).
divN(N,D)	:- N1 is N div 2, N1 < D.
divN(N,D)	:- divide(D,N), tab(1), write(D), fail.
divN(N,D)	:- D1 is D+1, divN(N,D1).
