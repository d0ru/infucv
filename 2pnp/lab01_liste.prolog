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

