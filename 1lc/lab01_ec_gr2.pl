% Rezolvarea ecuației de gradul 2

ec_grad2(0,B,C,X,X)	:-ec_grad1(B,C,X).
ec_grad2(A,B,C,X1,X2)	:- D is B*B-4*A*C, D > 0, RD is sqrt(D), X1 is (-B-RD)/(2*A), X2 is (-B+RD)/(2*A).
ec_grad2(A,B,C,X1,X2)	:- D is B*B-4*A*C, D = 0, X1 is -B/(2*A), X2 = X1).
ec_grad2(A,B,C,_,_)	:- D is B*B-4*A*C, D < 0, writeln('Nu exista solutii').

ec_grad1(0,0,_)	:- writeln('Solutie nedeterminata').
ec_grad1(0,_,_)	:- writeln('Nu exista solutie').
ec_grad1(A,B,X)	:- X is -B/A.
