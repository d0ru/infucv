% Să se calculeze diferența a două liste.

diferența(L,[],L).
diferența(L1,[X|R2],L)	:- șterge_elem(L1,X,L2), diferența(L2,R2,L).


% Șterge toate aparițiile unui element dintr-o listă.

șterge_elem([],_,[]).
șterge_elem([E|Rest],E,LE)	:- șterge_elem(Rest,E,LE).
șterge_elem([X|Rest],E,[X|LE])	:- șterge_elem(Rest,E,LE).
