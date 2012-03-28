% citire listă dintr-un fișier până când se ajunge la EOF
% calculează și afișează într-un alt fișier minimul, maximul si media lor
mmm	:- see('lab03.txt'), mmm([]), seen.
mmm(L)	:- read(N), N \= end_of_file, append(L,[N],Rez), mmm(Rez).
mmm(L)	:- fminim(L), fmaxim(L), fmedia(L).

fminim(L)	:- tell('minim.txt'), minim(L,M), writeln(M), told.
fmaxim(L)	:- tell('maxim.txt'), maxim(L,M), writeln(M), told.
fmedia(L)	:- tell('media.txt'), media(L,M), writeln(M), told.

minim([X], X).
minim([X|Rest], X)	:- minim(Rest, M), X < M.
minim([_|Rest], M)	:- minim(Rest, M).

maxim([X], X).
maxim([X|Rest], X)	:- maxim(Rest,M), X > M.
maxim([_|Rest], M)	:- maxim(Rest, M).

% Media aritmetică a tuturor numerelor unei liste.
suma([],0).
suma([X|Rest],S)	:- suma(Rest,S1), S is S1+X.
nr_elem([],0).
nr_elem([_|Rest],N)	:- nr_elem(Rest,N1), N is N1+1.
media([],0).
media(Lista,M)		:- suma(Lista,S), nr_elem(Lista,N), M is S/N.

