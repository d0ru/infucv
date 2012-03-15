% Adaugarea unui element într-o listă după un element dat.
% E elementul nou de adăugat în listă
% X elementul după care se adaugă în listă

% Elementul nou se adaugă doar după prima apariție a elementului X.

adaugă_dupăX([X|R1],E,X,[X,E|R1]).
adaugă_dupăX([Y|R1],E,X,[Y|R2])	:- adaugă_dupăX(R1,E,X,R2).


% Să se adauge un element la sfârșitul unei liste.

adaugă_ultimul(X,[],[X]).
adaugă_ultimul(X,[Y|R1],[Y|R2])	:- adaugă_ultimul(X,R1,R2).


% Să se adauge un element pe o poziție dată într-o listă.

adaugăN(L1,X,1,[X|L1]).
adaugăN([Y|R1],X,N,[Y|R2])	:- N1 is N-1, adaugăN(R1,X,N1,R2).

