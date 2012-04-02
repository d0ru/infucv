# FII'12 runda nr. 2

Dată început: 2012-04-02 00:00:00
Dată sfârşit: 2012-04-08 23:59:59


## Problema 1: joc

    In: joc.in | Out: joc.out | Timp: 0.5s | Memorie: 16 MB (3 MB stivă)

Se consideră un joc electronic în care tu trebuie să parcurgi un drum
lung, de-a lungul căruia se află «n» monștri. Fiecare monstru întâlnit
trebuie învins. Puterea fiecărui monstru `i = 1,2,..n` se măsoară în
unități convenționale și se notează prin `p[i]`.
Se mai cunoaște `b[i]` - bonus că ai ajuns la nivelul «i». (`b1 = 0`)

În orice moment din joc tu ai o viață `1 ≤ V ≤ 100` (inițial 100). Tu
trebuie să distrugi câte un monstru (în ordinea `1,2..n`) aplicând
contra fiecăruia din ei una din cele două arme pe care le ai la
dispoziție: sabia sau un cuvînt magic.

Dacă nimicești monstrul «i» cu ajutorul sabiei, pierzi din viata ta
`p[i]` unități. Dacă însă distrugi monstrul pronunțând cuvântul magic,
nu pierzi nimic din viața ta.

Dupa fiecare luptă viața ta trebuie să aibă cel puțin o unitate, altfel
ai pierdut jocul. După nimicirea monstrului «i-1», în drum spre monstrul
«i» viața ta crește cu `b[i]` unități.
Totuși, dacă în procesul creșterii valoarea `V + b[i]` ar putea deveni
mai mare ca `100`, valoarea curentă a vieții tale va crește doar până
la `100` de unități.


### Cerință

Scrie un program care te ajută să câștigi jocul astfel încât cuvântul
magic să fie pronunțat de un număr minimal de ori.


### Date de intrare

Fișierul text `joc.in` conține pe prima linie un singur număr întreg -
numărul de monștri «n».
Următoarele «n» linii ale fișierului de intrare conțin câte două numere
întregi separate prin spațiu `b[i] p[i]` ce descriu bonusul de nivel și
puterea monstrului «i».


### Date de ieșire

Fișierul text `joc.out` va conține pe o singură linie numărul întreg
`m` - numărul minim de utilizări ale cuvântului magic, suficient pentru
a învinge toți monștrii.


### Restricții și precizări

* 1 ≤ n ≤ 20000; 1 ≤ b[i],p[i] ≤ 100
* 1 ≤ n < 100 pentru 20% din teste
* 100 ≤ n < 10000 pentru 60% din teste
* 10000 ≤ n ≤ 20000 pentru 20% din teste


## Problema 2: video