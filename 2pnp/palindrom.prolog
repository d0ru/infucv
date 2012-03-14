% Construiește o listă cu toate cifrele unui număr dat «n».

cifre(N,[N])	:- N < 10, !.
cifre(N,L)	:- D is N div 10, M is N mod 10, cifre(D,LD), L = [M|LD].


% Inversul unei liste.

inversează(L,Linv)	:- inv1(L,[],Linv).
inv1([],L,L).
inv1([X|Rest],Ltmp,Linv):- inv1(Rest,[X|Ltmp],Linv).


% Determină dacă două liste de aceeași lungime sunt identice.

identice(L,L).


% Determină dacă un număr natural este palindrom (sau simetric).

nr_simetric(N)	:- N < 10, !.
nr_simetric(N)	:- cifre(N,L1), inversează(L1,L2), identice(L1,L2).

palindrom(N)	:- write('Numărul «'), write(N), write('»'), nr_simetric(N), writeln(' este simetric.').
palindrom(_)	:- writeln(' nu este simetric.').


% N - numărul de pornire, incrementat atât timp cât N < MAX
simetrice(MAX)	:- write('Numerele simetrice mai mici decât «'), write(MAX), write('» sunt:'), simN(MAX,1), writeln('.').
simN(MAX,N)	:- N > MAX.
simN(_,N)	:- nr_simetric(N), tab(1), write(N), fail.
simN(MAX,N)	:- N1 is N+1, simN(MAX,N1).
