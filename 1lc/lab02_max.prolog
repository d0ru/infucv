% Calculează maximul a două sau mai multe numere.

max2(X,Y,X)	:- X > Y.
max2(_,Y,Y).

max3(X,Y,Z,M)	:- max2(X,Y,M2), max2(M2,Z,M).
