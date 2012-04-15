# FII'12 runda nr. 3

`Dată început: 2012-04-09 00:00:00`  
`Dată sfârşit: 2012-04-15 23:59:59`


## Problema 1: Strunguri

    In: strung.in | Out: strung.out
    Timp: 1s | Memorie: 64 MB (din care 32 MB stivă)

Se consideră «m» strunguri identice destinate prelucrării automate a
unor piese. Strungurile funcționează independent unul de altul.
În procesul prelucrării piesele sunt avansate către strunguri cu
ajutorul unei benzi rulante.

Piesele de prelucrat sunt numerotate în ordinea apariției lor pe bandă
prin numerele naturale `1 2 3…n`.
Pentru fiecare piesă «i» se cunoaște timpul `d[i]` necesar pentru
prelucrarea ei pe unul din cele «m» strunguri.

### Cerință

Elaborați un program care calculează timpul `Q` necesar pentru a
prelucra toate piesele.

### Date de intrare

Fișierul text `strung.in` conține pe prima linie două numere naturale
`m n`, separate prin spațiu. Fiecare din următoarele «n» linii ale
fișierului de intrare conține câte un număr natural.
Linia «i+1» a fișierului de intrare conține numărul natural `d[i]` —
timpul necesar pentru prelucrarea piesei «i» pe unul din cele «m»
strunguri.

### Date de ieșire

Fișierul text `strung.out` va conține pe o singură linie numărul natural
`Q` — timpul necesar pentru a prelucra toate piesele.

    Exemplu
    -------
    [strung.in]     [strung.out]
    3 10            16
    1
    2
    3
    9
    7
    5
    2
    3
    4
    6

### Restricții și precizări

* ` 2 ≤ m ≤ 100`
* ` 1 ≤ n ≤ 1000`
* ` 1 ≤ d[i] ≤ 30`, i=1…n


## Problema 2: Insule

    In: insule.in | Out: insule.out
    Timp: 0.25s | Memorie: 64 MB (din care 32 MB stivă)

Pentru a atrage cât mai mulți turiști, guvernul țării Olimpia a decis să
construiască mai multe insule artificiale, legate între ele prin poduri.
Insulele au fost construite, iar acum sunt proiectate podurile.

Harta insulelor reprezintă un tabel bidimensional format din `n × m`
celule, fiecare celulă simbolizând o porțiune de uscat sau de apă.

Se consideră că un set de celule simbolizează o insulă atunci și doar
atunci când:

1) din fiecare din aceste celule se poate ajunge în oricare alta prin
treceri consecutive din celula curentă în cea vecină pe orizontală sau
pe verticală;

2) în afara acestui set nu mai există alte celule în care s-ar putea
trece.

Podurile vor fi proiectate conform următoarelor reguli:

* fiecare pot trebuie să fie construit pe verticală sau pe orizontală;
* podurile pot trece doar prin celulele ce simbolizează apa;
* orice pod începe și se termină în celule ce simbolizează uscatul;
* podurile se pot intersecta, fiind construite pe diferite nivele.

Costul unui pod este egal cu numărul de celule prin care el trece.


### Cerință

Elaborați un program care calculează costul sumar minimal `s` al unui
grup de poduri ce ar permite turiștilor să viziteze toate insulele.

### Date de intrare

Fișierul text `insule.in` conține pe prima linie numerele întregi
`n m`, separate prin spațiu. Fiecare din următoarele «n» linii ale
fișierului de intrare conține câte «m» caractere ce simbolizează
apa (0) sau uscatul (1).

### Date de ieșire

Fișierul text `insule.out` va conține pe o singură linie numărul întreg
`s`. Dacă grupul de poduri nu poate fi construit, în fișierul de ieșire
se va scrie numărul `-1`.

    Exemplu
    -------
    [insule.in]     [insule.out]
    5 5             8
    01110
    00100
    10010
    00100
    10001 

### Restricții și precizări

* ` 1 ≤ n,m ≤ 500`


## Problema 3: Dame

    In: dame.in | Out: dame.out
    Timp: 0.25s | Memorie: 32 MB (din care 16 MB stivă)

Fie o tablă de șah cu «n» linii și «m» coloane. Pe această tablă
sunt plasate mai multe dame și pioni. Ne interesează să aflăm numărul
de pătrățele pe care nu se află nici o piesă și care nu sunt în raza
de atac a nici unei dame. Vom numi aceste pătrățele “sigure”.

De exemplu, pe următoarea tablă există 7 pătrățele sigure.

    -----------------
    |   | P | × | D |
    -----------------
    |   |   | P | D |
    -----------------
    |   |   | × | × |
    -----------------
    |   | × |   | × |
    -----------------

Considerăm că o damă poate ataca orice poziție în una din direcțiile
verticală, orizontală sau diagonală, în total *8* direcții. Pătrățica
atacată poate fi la orice distanță, dar cu condiția ca drumul sprea ea
să nu fie blocat de nici o altă piesă. Pionul nu poate ataca.

De exemplu pe tabla de mai jos pătrățelele ce pot fi atacate de damă
sunt marcate cu un `×`:

    ---------------------
    |   | × | × | × |   |
    ---------------------
    | × | × | D | × | × |
    ---------------------
    |   | × | × | × |   |
    ---------------------
    | × |   | × |   | × |
    ---------------------
    |   |   | × |   |   |
    ---------------------

### Cerință

Fiind date pozițiile damelor și ale pionilor pe o tablă de șah, scrieți
un program care să calculeze numărul de pătrățele sigure de pe tablă.

### Date de intrare

Fișierul text `dame.in` conține pe prima linie două numere naturale
`n m` — numărul de linii, respectiv de coloane ale tablei de șah.
Pe a doua linie este scris `nd` — numărul de dame.
Pe următoarele «nd» linii vor fi scrise câte două numere `dx[i] dy[i]`
— linia și coloana pe care se află dama «i».

După acestea pe o nouă linie va fi scris `np` — numărul de pioni.
Pe ultimele «np» linii vor fi scrise câte două numere `px[j] py[j]` —
linia și coloana pe care se află cei «np» pioni.

### Date de ieșire

Fișierul text `dame.out` va conține pe o singură linie numărul de
pătrățele sigure `s`.

    Exemplu
    -------
    [dame.in]       [dame.out]
    4 4             7
    2
    1 4
    2 4
    2
    1 2
    2 3

### Restricții și precizări

* ` 1 ≤ n,m ≤ 1000`
* ` 0 ≤ nd,np ≤ 100`
* ` 1 ≤ dx[i],px[j] ≤ n`
* ` 1 ≤ dy[i],py[j] ≤ m`
