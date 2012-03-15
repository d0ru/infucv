% Poziția unui element într-o listă.

poziție_elem([],_,0).
poziție_elem(L,X,P)	:- poz_elem(L,X,1,P).
poz_elem([X|_],X,P,P).
poz_elem([_|Rest],X,C,P):- C1 is C+1, poz_elem(Rest,X,C1,P).


% Elementul de pe poziția «i» dintr-o listă.

poziție([X|_],1,X).
poziție([_|Rest],I,N)	:- I1 is I-1, poz(Rest,I1,N).


% Determinați ultimul element dintr-o listă.

ultim([X],X).			% sau ultim([X|[]],X).
ultim([_|Rest],X)	:- ultim(Rest,X).


% Verifică dacă două elemente sunt consecutive într-o listă.

elem_cons([X,Y|_],X,Y).
elem_cons([_,_|R],X,Y)	:- elem_cons(R,X,Y).


% Verifică dacă elemente unei liste sunt în ordire crescătoare.

or_cres([]).
or_cres([_]).
or_cres([X,Y|Rest])	:- X =< Y, or_cres([Y|Rest]).


% Elementul maxim al unei liste.

maxim([X|Rest])	:- max1(Rest,X).
max1([],M)	:- write('Elementul maxim este «'), write(M), writeln('».').
max1([X|Rest],M):- X < M, max1(Rest,M); max1(Rest,X).

max2([M])	:- write('Elementul maxim este «'), write(M), writeln('».').
max2([X,Y|Rest]):- X >= Y, max2([X|Rest]); max2([Y|Rest]).

max3([M],M).
max3([X|Rest],M):- max3(Rest,M1), X < M1, M = M1; M = X.


% Poziția pe care se află elementul maxim al unei liste.
% M elementul maxim
% P poziția elementului maxim curent
% N poziția elementului curent din listă

poz_maxim([M|Rest])	:- poz_max1(Rest,M,1,1).
poz_max1([],M,P,N)	:- write('Elementul maxim «'), write(M), write('» se află pe poziția '), write(P), write(' din '), write(N), writeln(' numere.').
poz_max1([X|Rest],M,P,N):- N1 is N+1, X < M, poz_max1(Rest,M,P,N1).
poz_max1([X|Rest],_,_,N):- N1 is N+1, poz_max1(Rest,X,N1,N1).


% Poziția pe care se află elementul minim al unei liste.

poz_minim([M|Rest])	:- poz_min1(Rest,M,1,1).
poz_min1([],M,P,N)	:- write('Elementul minim «'), write(M), write('» se află pe poziția '), write(P), write(' din '), write(N), writeln(' numere.').
poz_min1([X|Rest],M,P,N):- N1 is N+1, X > M, poz_min1(Rest,M,P,N1).
poz_min1([X|Rest],_,_,N):- N1 is N+1, poz_min1(Rest,X,N1,N1).

