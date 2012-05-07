% adaugă numerele prime mai mici decât N în baza de date construită dinamic

:- dynamic prim/1.

afis_dbprim	:- prim(X), write(X), write(' '), fail.
afis_dbprim.

nrprime(N)	:- N < 2, !.
nrprime(N)	:- N == 2, assert(prim(2)).
nrprime(N)	:- assert(prim(2)), nrprime(3,N).

nrprime(X,N)	:- X > N.
nrprime(X,N)	:- nrprim(3,X), assert(prim(X)), X2 is X+2, nrprime(X2, N).
nrprime(X,N)	:- X2 is X+2, nrprime(X2, N).

nrprim(K,N)	:- K >= N.
nrprim(K,N)	:- nu_divide(K,N), K2 is K+2, nrprim(K2,N).

divide(K,N)	:- P is N mod K, P == 0.
nu_divide(K,N)	:- P is N mod K, P =\= 0.

