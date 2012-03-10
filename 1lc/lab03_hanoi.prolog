% Problema turnurilor din Hanoi.
%
% Scopul acestui puzzle este de a muta n discuri de pe bara din stânga pe bara
% din dreapta folosind bara din centru ca pe una auxiliară. Important este că
% un disc mai mare nu poate fi așezat pe un disc mai mic și la un moment dat
% poate fi mutat numai unul.
%
% Interogarea va arăta astfel:
%?- muta(3, stanga, dreapta, centru).

% X - turnul pe care se află discurile
% Y - turnul pe care sunt mutate discurile de pe X
% Z - turnul intermediar
muta(1,X,Y,_)	:- write('Mută discul din '), write(X), write(' în '), write(Y), nl.
muta(N,X,Y,Z)	:- N > 1, N1 is N-1, muta(N1,X,Z,Y), muta(1,X,Y,_), muta(N1,Z,Y,X).

% D - dimensiunea discului
hanoi(N,X,Y,Z)	:- hanoiN(N,N,X,Y,Z).
hanoiN(1,D,X,Y,_)	:- write('Mută discul ('), write(D), write(') din '), write(X), write(' în '), write(Y), nl.
hanoiN(N,D,X,Y,Z)	:- N1 is N-1, D1 is D-1, hanoiN(N1,D1,X,Z,Y), hanoiN(1,N,X,Y,_), hanoiN(N1,D1,Z,Y,X).
