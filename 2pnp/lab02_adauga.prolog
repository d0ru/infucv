% Adaugarea unui element într-o listă după un element dat.
% LO lista originală
% E elementul nou de adăugat în listă
% X elementul după care se adaugă în listă

% Elementul nou se adaugă doar după prima apariție a elementului X.

adaugă([X|R1],E,X,[X,E|R1]).
adaugă([Y|R1],E,X,[Y|R2])	:- adaugă(R1,E,X,R2).
