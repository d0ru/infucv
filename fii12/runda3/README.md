# FII'12 runda nr. 3

`Dată început: 2012-04-09 00:00:00`  
`Dată sfârşit: 2012-04-15 23:59:59`


## Problema 1: Strunguri

    In: strung.in | Out: strung.out
    Timp: 1s | Memorie: 64 MB (din care 32 MB stivă)

### Cerință

Elaborați un program care calculează timpul necesar pentru a prelucra
toate piesele.


## Problema 2: Insule

    In: insule.in | Out: insule.out
    Timp: 0.25s | Memorie: 64 MB (din care 32 MB stivă)

### Cerință

Elaborați un program care calculează costul sumar minimal `s` al unui
grup de poduri ce ar permite turiștilor să viziteze toate insulele.


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
    |   | × | × | × |
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
