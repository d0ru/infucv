% Arbori binari în Prolog

arb(8, arb(4, arb(3,n,n), arb(6,n,n)), arb(11, arb(9,n,n), arb(16,n,n))).


% suma elementelor arborelui binar

suma(n, 0).
suma(arb(R,n,n), R).
suma(arb(R,ArbS,ArbD), Suma)	:- suma(ArbS,S1), suma(ArbD,S2), Suma is R+S1+S2.


% verifică existența unui număr dat într-un arbore binar

caută(n, X)	:- write('Numărul «'), write(X), writeln('» nu a fost găsit.').
caută(arb(X,_ArbS,_ArbD), X)	:- write('Numărul «'), write(X), writeln('» a fost găsit.').
caută(arb(R,ArbS,_ArbD), X)	:- X < R, caută(ArbS, X).
caută(arb(_,_ArbS,ArbD), X)	:- caută(ArbD, X).


% parcurgerea unui arbore binar în preordine
% (radacina, subarborele stang, subarborele drept)

preordine(n).
%preordine(arb(R,n,n))	:- write(' '), write(R).
preordine(arb(R,ArbS,ArbD))	:- write(' '), write(R), preordine(ArbS), preordine(ArbD).


% parcurgerea unui arbore binar în inordine
% (subarborele stang, radacina, subarborele drept)
% (parcurgere în ordine crescătoare)

inordine(n).
%inordine(arb(R,n,n))	:- write(' '), write(R).
inordine(arb(R,ArbS,ArbD))	:- inordine(ArbS), write(' '), write(R), inordine(ArbD).


% parcurgerea unui arbore binar în postordine
% (subarborele stang, subarborele drept, radacina)

postordine(n).
%postordine(arb(R,n,n))	:- write(' '), write(R).
postordine(arb(R,ArbS,ArbD))	:- postordine(ArbS), postordine(ArbD), write(' '), write(R).


% inserarea unui element in cadrul arborelui
% (regula 2 evită duplicarea unui element existent)

inserare(n, X, arb(X,n,n)).
inserare(arb(R,ArbS,ArbD), R, arb(R,ArbS,ArbD)).
inserare(arb(R,ArbS,ArbD), X, arb(R,ArbS1,ArbD))	:- X < R, inserare(ArbS, X, ArbS1).
inserare(arb(R,ArbS,ArbD), X, arb(R,ArbS,ArbD1))	:- X > R, inserare(ArbD, X, ArbD1).

