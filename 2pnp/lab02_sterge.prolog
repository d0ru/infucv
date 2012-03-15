% Să se șteargă un element de pe o anumită poziție dintr-o listă.

șterge([_|R1],1,R1).
șterge([X|R1],N,[X|R2])	:- N1 is N-1, șterge(R1,N1,R2).


% Să se șteargă un element aflat inaintea unui element dat dintr-o listă.
% Elementul se șterge doar după prima apariție a elementului X.

ștergeX([],_,[]).
ștergeX([X],_,[X]).
ștergeX([_,X|Rest],X,[X|Rest]).
ștergeX([Y|R1],X,[Y|R2])	:- ștergeX(R1,X,R2).


% Să se șteargă toate aparițiile unui element dintr-o listă.

șterge_elem([],_,[]).
șterge_elem([E|Rest],E,LE)	:- șterge_elem(Rest,E,LE).
șterge_elem([X|Rest],E,[X|LE])	:- șterge_elem(Rest,E,LE).


% Eliminarea duplicatelor dintr-o listă.

elim_dup([],[]).
elim_dup([X|R1],L2)	:- member(X,R1), elim_dup(R1,L2).
elim_dup([X|R1],[X|R2])	:- elim_dup(R1,R2).

