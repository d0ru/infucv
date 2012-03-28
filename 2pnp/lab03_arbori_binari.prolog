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


% creați o listă ordonată din elementele unui arbore binar de căutare

lordonată(n, []).
lordonată(arb(R,n,n), [R]).
lordonată(arb(R,ArbS,ArbD), L)	:- lordonată(ArbS,LS), append(LS,[R],L1), lordonată(ArbD,LD), append(L1,LD,L).


% să se creeze un arbore binar de căutare cu elementele unei liste de numere

mkarbb(L, ArbBRez)	:- mkarbb(L, n, ArbBRez).
mkarbb([], ArbBRez, ArbBRez).
mkarbb([X|Rest], A1, ARez)	:- inserare(A1,X,A2), mkarbb(Rest, A2, ARez).


% calculează numărul de elemente dintr-un arbore binar de căutare

nrelem(n, 0).
nrelem(arb(_R,ArbS,ArbD), N)	:- nrelem(ArbS, N1), nrelem(ArbD, N2), N is N1 + N2 + 1.


% Pentru un arbore binar de cautare dat, sa se compare lungimile (numarul de elemente) celor doi subarbori atasati radacinii.

cmpsubarb(n) 	:- writeln('Arborul binar vid.').
cmpsubarb(arb(_R,ArbS,ArbD))	:- nrelem(ArbS,S), nrelem(ArbD,D), S == D, writeln('Arborele binar este echilibrat.').
cmpsubarb(arb(_R,ArbS,ArbD))	:- nrelem(ArbS,S), nrelem(ArbD,D), S > D, writeln('Arborele binar are mai multe elemente în ramura stângă.').
cmpsubarb(arb(_R,ArbS,ArbD))	:- writeln('Arborele binar are mai multe elemente în ramura dreaptă.').

