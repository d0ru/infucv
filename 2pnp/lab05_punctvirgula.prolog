% înlocuiește fiecare caracter «.» cu caracterul «,» dintr-un fișier
punctvirg	:- see('lab05.txt'), tell('lab05.out'), pv_citesc, seen, told.

pv_citesc	:- get(C), C =\= -1, pv_scriu(C), pv_citesc.
pv_citesc.
pv_scriu(C)	:- C == 46, put(,).
pv_scriu(C)	:- C == 32, write('spatiu').
pv_scriu(C)	:- put(C).

