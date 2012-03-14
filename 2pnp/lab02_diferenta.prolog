% Să se calculeze diferența a două liste.

diferența(L,[],L).
diferența(L1,[X|R2],L)	:- șterge_elem(L1,X,L2), diferența(L2,R2,L).

diferența2([],_,[]).
diferența2([X|R1],L2,L)	:- member(X,L2), diferența2(R1,L2,L).
diferența2([X|R1],L2,[X|R2])	:- diferența2(R1,L2,R2).


% Șterge toate aparițiile unui element dintr-o listă.

șterge_elem([],_,[]).
șterge_elem([E|Rest],E,LE)	:- șterge_elem(Rest,E,LE).
șterge_elem([X|Rest],E,[X|LE])	:- șterge_elem(Rest,E,LE).
