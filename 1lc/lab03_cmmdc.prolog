% CMMDC - cel mai mare divizor comun a două numere naturale
% http://ro.wikipedia.org/wiki/Cel_mai_mare_divizor_comun

%cmmdc(1,_,1).
%cmmdc(_,1,1).
%cmmdc(A,A,A).
cmmdc(A,0,A).
cmmdc(A,B,C)	:- A >= B, Rest is A mod B, cmmdc(B,Rest,C).
cmmdc(A,B,C)	:- A < B, Rest is B mod A, cmmdc(A,Rest,C).

