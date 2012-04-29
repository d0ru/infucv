# FII'12 runda nr. 4

`Dată început: 2012-04-23 00:00:00`  
`Dată sfârşit: 2012-04-29 23:59:59`


## Problema 1: Recoltabin

    In: recoltabin.in | Out: recoltabin.out
    Timp: 1s | Memorie: 64 MB (din care 32 MB stivă)

Propunător: Amazon Development Center Romania

Un gospodar are în fața casei un copac binar, fructifer, echilibrat, frumos și foarte roditor cu «N» ramuri. Fiecare ramură a copacului are un anumit număr de fructe `1 ≤ p ≤ 1000`.
Fructele se culeg tăind ramurile pe care acestea sunt așezate. Când se taie o ramură se recoltează odată cu ea și toate ramurile care sunt subramuri ale acesteia.

Vine toamna și gospodarul nostru vrea să culeagă fructele, însă pentru că este un copac așa de frumos nu le va culege pe toate. Mai precis el ar fi mulțumit să aibă o recoltă de minimum `1 ≤ S ≤ 10⁶` fructe.

Toate bune însă gospodarul nostru este un om mai special. Vrea să muncească puțin, adică să facă un număr maxim de tăieturi `1 ≤ K ≤ 100`. Mai mult, el vrea să taie acele ramuri care sunt mai puțin roditoare, pentru ca sa rămână copacul cât mai frumos chiar și după culegerea recoltei. El vrea ca să strângă o recoltă de minim «S», unde cea mai mare ramură din ramurile colectate să aibă o cantitate cât mai mică.
De exemplu avem copacul urmator, care are 7 ramuri, iar gospodarul doreste o recolta de S=6 fructe si este dispus sa faca maximum k=2 taieturi.

      \6 /3\1 /1
       \/   \/
        \5 /2
         \ /
          |
          |7

El poate obține recolta cu o singură tăietură, recoltând numai ramura cu greutate „6”. Însă aceasta nu este soluția optimă pentru că cea mai mare ramură recoltată are greutate 6.

O soluție optimă a acestei probleme este să taie ramurile cu valoare „3” și „2”. Recolta obținută ar fi `3 + 2 + 1 + 1 = 7 ≥ S`. Numărul de tăieturi este `2 ≤ K`, deci nu muncește mai mult decât trebuie, iar greutatea maximă a unei ramuri recoltate este `3` (cea mai mare dintre ramurile 3,1,1,2).

### Date de intrare

Programul tău va citi de pe prima linie a fișierului de intrare `recoltabin.in` numerele `N K S`. De pe a doua linie se vor citi greutățile (numerele de fructe) pentru fiecare ramură «i» ale arborelui, cu `1 ≤ i ≤ N`. Ramura «1» este ramura rădăcină. Ramura «2» este ramura stângă care pornește din rădăcină, «3» fiind ramura dreaptă care pornește din rădăcină. Ramurile «4,5» sunt ramurile din stânga, respectiv dreapta ale ramurii «2» și așa mai departe.

### Date de ieșire

Programul tău va scrie pe o linie a fișierului de ieșire `recoltabin.out` valoarea celei mai grele ramuri dintr-o recoltă optimă. O recoltă optimă este mai mare decat `S`, realizată din maximum `K` tăieturi și minimizează valoarea celei mai grele ramuri recoltate.

    Exemplu
    -------
    [recoltabin.in]      [recoltabin.out]
    ~~~~~~~~~~~~~~~~~~~~~~~~
    7 2 6                | 3
    7 5 2 6 3 1 1        |
    ~~~~~~~~~~~~~~~~~~~~~~~~
    5 2 2                | 4
    6 5 5 1 4            |
    ~~~~~~~~~~~~~~~~~~~~~~~~

### Restricții și precizări

* `1 ≤ n ≤ 4000`
* `1 ≤ p ≤ 1000`
* `1 ≤ s ≤ 1000000`
* `1 ≤ k ≤ 100`


## Problema 2: Arcaș

    In: arcas.in | Out: arcas.out
    Timp: 2s | Memorie: 64 MB (din care 32 MB stivă)

Un turneu de tir cu arcul este organizat în conformitate cu următoarele reguli.
Există «N» ținte aranjate într-o linie și numerotate de la «1» la «N» inclusiv, în funcție de poziția lor pe linie (ținta cea mai din stânga fiind «1», ținta cea mai din dreapta fiind ținta «N»).
Există, de asemenea, «2•N» arcași.

În orice moment în timpul turneului, sunt doi arcași la fiecare țintă în competiție unul cu celălalt: un câștigător și un învins.
Apoi, toți arcașii sunt rearanjați după cum urmează: câștigătorii de pe țintele de la «2» la «N» inclusiv se mută la ținta din stânga lor (adică la țintele de la «1» la «N-1»).
Perdanții de pe țintele de la «2» la «N» inclusiv, precum și câștigătorul de la ținta «1» rămân la aceeași țintă.
Pierzătorul de la ținta «1» se mută la ținta «N».

Turneul continuă pentru «R» runde, cu numărul de runde fiind cel puțin la fel de mare ca numărul de arcași.
Sunteți singurul arcaș care ajunge la turneu exact la ora planificata. Toti ceilalți «2•N-1» arcași au ajuns mai devreme și sunt așezați deja în linie. Ce ai tu de făcut acum este să intri undeva în linie printre ei. Știi că după ce te așezi în linie cei doi arcași cei mai din stânga vor începe sa tragă în ținta 1, urmatorii doi in ținta 2 s.a.m.d.

Toți cei «2•N» arcași din turneu (inclusiv tu) sunt clasificați în funcție de abilitate, unde un rang mai mic semnifică o abilitate mai buna. Oricare doi arcași au rang diferit. De fiecare dată când doi arcași concurează unul împotriva celuilalt, cel cu rangul cel mai mic câștigă.

Știind cât de abili sunt competitorii, dorești să te așezi pe o poziție în linie care să îți asigure o poziție la final cât mai mică (cât mai spre stânga). Dacă sunt mai multe moduri de a face asta, îl vei prefera pe cel în care începi pe o poziție cât mai în dreapta (un număr cât mai mare).

### Cerință

Scrie un program care, primind rangurile arcașilor incluzând pe al tău, precum și aranjamentul în linie al competitorilor, determină la care țintă vei începe turneul astfel încât îți vei împlini scopul așa cum este prezentat mai sus.

### Date de intrare

Programul tău trebuie să citească din `arcas.in` următoarele: prima linie conține întregii `N R` separați prin câte un spațiu. Următoarele «2•N» linii conțin rangurile arcașilor.

Prima linie conține rangul tău, următoarele linii, în ordinea în care sunt scrise (de sus în jos) reprezintă rangurile arcașilor după cum sunt așezați (de la stânga la dreapta).
Fiecare dintre aceste linii conține un singur întreg «S[k]». Rangul «1» este cel mai bun, rangul «2•N» este cel mai prost. Nu sunt doi arcași cu acelasi rang.

### Date de ieșire

Programul tău trebuie să scrie în `arcas.out` o singură linie ce conține un singur întreg între «1» și «N» inclusiv: numărul țintei de la care începi turneul.

    Exemplu
    -------
    [arcas.in]      [arcas.out]
    4 8             3
    7
    4
    2
    6
    5
    8
    1
    3

### Restricții și precizări

* `1 ≤ N ≤ 200 000`
* `2•N ≤ R ≤ 1 000 000 000`
* `1 ≤ S[k] ≤ 2•N`


## Problema 3: Puncte

    In: puncte.in | Out: puncte.out
    Timp: 0.25s | Memorie: 32 MB (din care 16 MB stivă)

Se consideră «n» puncte distincte pe un plan cartezian, denumite „puncte convenționale”. De asemenea, mai sunt date încă două puncte distincte, denumite „puncte de bază”.

### Cerință

Elaborați un program care calculează numărul maximal de puncte convenționale «m» ce pot fi incluse într-o „panglică” formată din două drepte paralele ce trec prin punctele de bază.

Punctele de bază nu vor fi incluse în numărul de puncte calculat. Punctele convenționale, care ar putea să se afle pe dreptele respective, vor fi incluse în numărul căutat de puncte.

### Date de intrare

Fișierul text `puncte.in` conține pe prima linie numărul întreg `n`.
Linia a doua a fișierului de intrare conține patru numere întregi separate prin spațiu — coordonatele `x1 y1 x2 y2` ale punctelor de bază.

Fiecare din următoarele «n» linii ale fișierului de intrare conține câte două numere întregi separate prin spațiu — coordonatele `x y` ale unui punct convențional.

### Date de ieșire

Fișierul text `puncte.out` va conține pe o singură linie numărul întreg `m`.

    Exemplu
    -------
    [puncte.in]     [puncte.out]
    4               3
    0 0 50 0
    0 -50
    -1 0
    50 0
    100 50

### Restricții și precizări

* `0 ≤ n ≤ 10000`
* coordonatele punctelor sunt numere întregi, modulul cărora nu depășește valoarea `10000`
