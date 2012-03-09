% LAB 02 (2012/03/09)
% -------------------
%
% In fiecare cameră se găsesc următoarele lucruri. In birou: masă, computer,
% scaun. In hol avem un cuier. In living avem un televizor, bibliotecă, canapea,
% fotolii și cărți. In bucătărie avem aragaz, frigider, masă, scaune, biscuiți
% și mere. La subsol mașină de spălat, șoricei și rufe murdare.
%
% Definiți legăturile dintre camere (eventual printr-un predicat numit ușă),
% locurile unde sunt situate diferite obiecte.
%
% Daca apelez un predicat [?-start(CAMERA).] sistemul să spună care este camera
% în care este plasat obiectul, care sunt camerele unde pot trece direct, ce
% obiecte găsești în cameră.

% ?-start(bucătărie).
% Te afli în bucătărie.
% Poți merge în:
% birou
% ..
% Poți vedea:
% aragaz
% ..

% ---------------------------
% |          Birou          |
% -------X-------------X-----
% |     Hol     |           |
% -------X------| Bucătărie |-----------
% |   Living    X           X  Subsol  |
% --------------------------------------

usa(birou, hol).
usa(birou, bucătărie).
usa(hol, living).
usa(living, bucătărie).
usa(bucătărie, subsol).

vede(birou, masa).
vede(birou, computer).
vede(birou, scaun).
vede(hol, cuier).
vede(living ,televizor).
vede(living, bibliotecă).
vede(living, canapea).
vede(living, fotolii).
vede(living, cărți).
vede(bucătărie, aragaz).
vede(bucătărie, frigider).
vede(bucătărie, masă).
vede(bucătărie, scaune).
vede(bucătărie, biscuiți).
vede(bucătărie, mere).
vede(subsol, mașină).
vede(subsol, spălat).
vede(subsol, șoricei).
vede(subsol, 'rufe murdare').

conectat(X,Y) :- usa(X,Y).
conectat(X,Y) :- usa(Y,X).

merge(X) :- conectat(X,Y), writeln(Y), fail.
merge(_).

obiecte(X) :- vede(X,Y), writeln(Y), fail.
obiecte(_).

start(X) :- write('Te afli în '), write(X), writeln('.'), writeln('Poți merge în:'), merge(X), writeln('Poți vedea:'), obiecte(X).
