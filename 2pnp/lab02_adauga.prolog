% Adaugarea unui element într-o listă după un element dat.
% LO lista originală
% E elementul nou de adăugat în listă
% X elementul după care se adaugă în listă

% Elementul nou se adaugă doar după prima apariție a elementului X.

adaugă([X|R1],E,X,[X,E|R1]).
adaugă([Y|R1],E,X,[Y|R2])	:- adaugă(R1,E,X,R2).


% Să se adauge un element pe o poziție dată într-o listă.

adaugăN(L1,X,1,[X|L1]).
adaugăN([Y|R1],X,N,[Y|R2])	:- N1 is N-1, adaugăN(R1,X,N1,R2).
