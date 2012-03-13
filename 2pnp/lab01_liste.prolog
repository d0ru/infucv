% Afișarea elementelor unei liste.

afișare([]).
afișare([X|Rest])	:- writeln(X), afișare(Rest).


% Să se verifice dacă un element dat aparține unei liste.

aparține(X,[X|_]).
aparține(X,[_|Rest])	:- aparține(X,Rest).


% Determinați numărul elementelor dintr-o listă.

nr_elem([],0).
nr_elem([_|Rest],N)	:- nr_elem(Rest,N1), N is N1+1.


% Determinați numărul elementelor *pozitive* dintr-o listă.

nr_elem_poz([],0).
nr_elem_poz([X|Rest],P)	:- X >= 0, nr_elem_poz(Rest,P1), P is P1+1.
nr_elem_poz([_|Rest],P)	:- nr_elem_poz(Rest,P).


% Determinați ultimul element dintr-o listă.

ultim([X],X).			% sau ultim([X|[]],X).
ultim([_|Rest],X)	:- ultim(Rest,X).


% Media aritmetică a tuturor numerelor unei liste.

suma([],0).
suma([X|Rest],S)	:- suma(Rest,S1), S is S1+X.
media([],0).
media(Lista,M)		:- suma(Lista,S), nr_elem(Lista,N), M is S/N.


% Suma tuturor numerelor pozitive ale unei liste.

suma_poz([],0).
suma_poz([X|Rest],S)	:- X > 0, suma_poz(Rest,S1), S is S1+X.
suma_poz([_|Rest],S)	:- suma_poz(Rest,S).


% Calculați suma pătratelor unei liste.

suma_patrate([],0).
suma_patrate([0|Rest],S):- suma_patrate(Rest,S).
suma_patrate([X|Rest],S):- P is X*X, suma_patrate(Rest,S1), S is P+S1.


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


% Poziția «i» dintr-o listă

poziție([X|_],1,X).
poziție([_|Rest],I,N)	:- I1 is I-1, poz(Rest,I1,N).


% Poziția unui element într-o listă

poziție_elem([],_,0).
poziție_elem(L,X,P)	:- poz_elem(L,X,1,P).
poz_elem([X|_],X,P,P).
poz_elem([_|Rest],X,C,P):- C1 is C+1, poz_elem(Rest,X,C1,P).


% Compararea lungimii a două liste

compar([],[])	:- writeln('Cele două liste au același număr de elemente.').
compar([_L],[])	:- writeln('Prima listă are mai multe elemente decât cea de a doua.').
compar([],[_L])	:- writeln('A doua listă are mai multe elemente decât prima.').
compar([_X|R1],[_Y|R2])	:- compar(R1,R2).


% Să se inverseze o listă.
% NU se poate adăuga un element la coada listei!!
% NU se pot concatena direct două liste!!
inversează(L,Linv)	:- inv1(L,[],Linv).
inv1([],L,L).
inv1([X|Rest],Ltemp,Linv)	:- inv1(Rest,[X|Ltemp],Linv).


% Interclasarea a două liste. Cele două liste trebuie să fie ordonate crescător.
% Elementele liste rezultate trebuie să fie de asemenea ordonate crescător.

interclasare(L1,L2,Lic)	:- intercl(L1,L2,[],Lic).
intercl([],[],L,Lic)	:- inversează(L,Lic).
intercl([X|R1],[],Ltemp,Lic)	:- intercl(R1,[],[X|Ltemp],Lic).
intercl([],[X|R2],Ltemp,Lic)	:- intercl([],R2,[X|Ltemp],Lic).
intercl([X|R1],[X|R2],Ltemp,Lic):- intercl(R1,R2,[X|Ltemp],Lic).
intercl([X|R1],[Y|R2],Ltemp,Lic):- X < Y, intercl(R1,[Y|R2],[X|Ltemp],Lic).
intercl([X|R1],[Y|R2],Ltemp,Lic):- intercl([X|R1],R2,[Y|Ltemp],Lic).

interclasez([],L,L).
interclasez(L,[],L).
interclasez([X|R1],[X|R2],[X|R3])	:- interclasez(R1,R2,R3).
interclasez([X1|R1],[X2|R2],[X1|R3])	:- X1 < X2, interclasez(R1,[X2|R2],R3).
interclasez([X1|R1],[X2|R2],[X2|R3])	:- interclasez([X1|R1],R2,R3).


% Să se șteargă toate aparițiile unui element dintr-o listă.

sterge_elem([],_,[]).
sterge_elem([E|Rest],E,LE)	:- sterge_elem(Rest,E,LE).
sterge_elem([X|Rest],E,[X|LE])	:- sterge_elem(Rest,E,LE).


% Eliminarea duplicatelor dintr-o listă.

elim_dup([],[]).
elim_dup([X|R1],L2)	:- aparține(X,R1), elim_dup(R1,L2).
elim_dup([X|R1],[X|R2])	:- elim_dup(R1,R2).


% Sublista care conține numai pozițiile pare (2, 4, 6, ...) din lista inițială.

poz_pare([],[]).
poz_pare([_],[]).
poz_pare([_,Y|Rest],[Y|Lpare])	:- poz_pare(Rest,Lpare).


% Poziții pare, poziții impare
% Se dă o listă: să se obțină două liste din aceasta astfel
% încât prima din ele să conțină elementele de pe
% pozițiile pare iar a doua pe cele de pe pozițiile impare.

parimpar([],[],[]).
parimpar([X],[X],[]).
parimpar([X,Y|Rest],[X|RImp],[Y|RPar])	:- parimpar(Rest,RImp,RPar).


% Verifică dacă două elemente sunt consecutive într-o listă.

cons2([X,Y|_],X,Y).
cons2([_,_|R],X,Y)	:- cons2(R,X,Y).


% Prefixul unei liste: primele N elemente ale unei liste
% Sufixul unei liste: ultimele M elemente ale unei liste

% Prefixul unei liste

prefix([],_L).
prefix([X|R1],[X|R2])	:- prefix(R1,R2).

% Sufixul unei liste

sufix(L,L).
sufix(L,[_X|R2])	:- sufix(L,R2).

% Sublista unei liste: daca este sufixul prefixului listei mari

sublista(L1,L2)		:- prefix(L,L2), sufix(L1,L).
