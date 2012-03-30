# FII'12 runda nr. 1

Data început: 26.03.2012  
Data sfârșit: 11:59 01.04.2012


## Problema 1: Inversiuni

Fie `x1, x2,.. xn` o secvență de «n» numere întregi distincte.
Perechea `(i,j)` se numește inversiune dacă `xi > xj` cu `1 ≤ i < j ≤ n`.

Exemplu: secvența "2 4 3 1 5 6 9" are 4 inversiuni.


### Date de intrare

Fișierul de intrare «inversiuni.in» conține secvențe nevide de numere
întregi. Fiecare secvență începe cu un număr `1 ≤ n ≤ 10000` care
specifică numărul de numere întregi din secvență. Acesta nu face parte
din secvență. Numerele pot fi separate prin spațiu, tab sau linie nouă.
Date din fișierul de intrare se consideră a fi corecte.


### Date de ieșire

Fișierul «inversiuni.out» conține pe câte o linie separată numărul de
inversiuni corespunzător fiecărei secvențe din fișierul de intrare.


### Cerință

Scrieți un program care pentru fiecare secvență de numere citită din
fișierul de intrare, scrie în fișierul de ieșire numărul de inversiuni
din secvență. Fiecare rezultat va fi scris pe o linie separată.


## Problema 2: Cutii

Se consideră cutii n-dimensionale date de cele «n» dimensiuni numere
întregi, strict pozitive. De exemplu (2, 9, 7) reprezintă o cutie
tri-dimensională, în timp ce (6, 2, 4, 1, 5) reprezintă o cutie
cinci-dimensională.  
Spunem că o cutie `x = (x1,x2,..xn)` încape în cutia `y = (y1,y2,..yn)`
dacă există o permutare a dimensiunilor cutiei x astfel încât:

    x[i] < y[i], ∀i = 1,n

Exemplu 1: cutia (7, 4) încape în cutia (5, 9) deoarece poate fi
rearanjată ca (4, 7) și fiecare dimensiune este mai mică decât
dimensiunea corespunzătoare cutiei (5, 9).

Exemplu 2: cutia (3, 4, 5, 6) nu încape în cutia (5, 9, 7, 1), deoarece
nici o rearanjare nu va satisface proprietatea de mai sus.

### Date de intrare

Fișierul «cutii.in» conține o serie de secvențe de cutii. Fiecare
secvență începe cu o linie conținând numărul de cutii «m», urmat de
dimensiunea cutiilor «n». Pe următoarele «m» linii se află cele «n»
dimensiuni ale fiecărei cutii.

    Exemplu 1
    ---------
    4 2		//m=4 , n=2
    3 8
    9 10
    4 2
    12 10

    Exemplu 2
    ---------
    6 4		//m=6, n=4
    7 18 3 20
    8 30 20 5
    9 13 15 17
    10 11 12 13
    1 2 3 4
    70 65 15 12

### Date de ieșire

Pentru fiecare set de intrare se va scrie în fișierul «cutii.out»
lungimea și cel mai lung șir de cutii ce încap una în alta. Pentru
exemplul de mai sus fișierul de ieșire va conține:

    Exemplu 1
    ---------
    4		// lungimea secvenței
    3 1 2 4	// cutia 3 încape în cutia 1 încape în cutia 2, toate
    		// încăpând în cutia 4

    Exemplu 2
    ---------
    4		// lungimea secvenței
    5 1 2 6	// cutia 5 încape în cutia 1 încape în cutia 2, toate
    		// încăpând în cutia 6

### Cerință

Dată o mulțime de cutii n-dimensionale, să se determine cea mai lungă
secvență de cutii `c1,c2,..ck` ce pot fi incluse una în alta. Adică,
cutia c[i] încape în cutia c[i+1], pentru `1 ≤ i < k`.

### Restricții și precizări

Dimensiunea minimă a cutiilor este 1, iar cea maximă este 10.
Numărul maxim de cutii dintr-o mulțime este 20.
