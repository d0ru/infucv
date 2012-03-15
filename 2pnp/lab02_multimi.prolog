% Reuniunea a două mulțimi.

reuniune(L,[],L).
reuniune([],L,L).
reuniune([X|R1],L2,L)	:- member(X,L2), reuniune(R1,L2,L).
reuniune([X|R1],L2,[X|R])	:- reuniune(R1,L2,R).


% Intersecția a două mulțimi.

intersecție(_,[],[]).
intersecție([],_,[]).
intersecție([X|R1],L2,[X|R])	:- member(X,L2), intersecție(R1,L2,R).
intersecție([_|R1],L2,R)	:- intersecție(R1,L2,R).

