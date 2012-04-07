# FII'12 runda nr. 2

Dată început: `2012-04-02 00:00:00`  
Dată sfârşit: `2012-04-08 23:59:59`


## Problema 1: Joc

    In: joc.in | Out: joc.out
    Timp: 0.5s | Memorie: 16 MB (din care 3 MB stivă)

Se consideră un joc electronic în care trebuie să parcurgi un drum
lung, de-a lungul căruia se află «n» monștri. Fiecare monstru întâlnit
trebuie învins. Puterea fiecărui monstru `i = 1,2,..n` se măsoară în
unități convenționale și se notează prin `p[i]`.
Se mai cunoaște `b[i]`, un bonus primit la începutul nivelului «i».

În orice moment din joc ai o viață `1 ≤ V ≤ 100` (inițial 100).
Trebuie să parcurgi fiecare nivel `1, 2.. n` aplicând contra fiecărui
monstru una din cele două arme pe care le ai la dispoziție: sabia sau
un cuvânt magic.

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
numărul de monștri `n`.
Următoarele «n» linii ale fișierului de intrare conțin câte două numere
întregi separate prin spațiu `bi pi` ce reprezintă bonusul de nivel și
puterea monstrului «i».

    [joc.in]
    4
    00 20
    30 40
    30 60
    20 80


### Date de ieșire

Fișierul text `joc.out` va conține pe o singură linie numărul întreg
`m` - numărul minim de utilizări ale cuvântului magic, suficient pentru
a învinge toți monștrii.

    [joc.out]
    1


### Restricții și precizări

* `1 ≤ n ≤ 20000`; `1 ≤ b[i],p[i] ≤ 100`
* `1 ≤ n < 100` pentru 20% din teste
* `100 ≤ n < 10000` pentru 60% din teste
* `10000 ≤ n ≤ 20000` pentru 20% din teste


## Problema 2: Video la comandă

    In: video.in | Out: video.out
    Timp: 0.1s | Memorie: 8 MB (din care 2 MB stivă)

Compania _VideoDava_ oferă prin intermediul rețelei globale Internet un
nou serviciu - filme video la comandă. Filmele pot fi vizionate cu
ajutorul unui program de navigare în Internet. Pentru o reproducere
calitativă a filmelor, se cere ca viteza de transmisie a informației
de la site-ul firmei către calculatorul abonatului să fie de cel puțin
«b» octeți pe secundă.

Însă, fără a mai consulta cerințele tehnice, Păcală și-a conectat
calculatorul la Internet printr-un canal cu capacitatea de transmisie a
informației de «d» octeți pe secundă, `d < b`. În consecință, filmele
nu mai pot fi reproduse în timp real, programul de navigare fiind nevoit
să utilizeze o memorie tampon de capacitate «s» octeți.

Programul respectiv funcționează după cum urmează:

1. Inițial, programul încarcă de pe site-ul firmei _VideoDava_ în
memoria tampon primul fragment al filmului video. Evident, acest
fragment va conține exact «s» octeți.

2. Imediat ce memoria tampon este umplută, programul începe reproducerea
fragmentului respectiv citind din memoria tampon câte «b» octeți pe
secundă.

3. Concomitent cu reproducerea fragmentului din memoria tampon, programul
încarcă de pe site-ul firmei (cu o viteză de «d» octeți pe secundă)
următorul fragment al filmului, memorând octeții respectivi în spațiul
ce se eliberează al memoriei tampon.

4. Întrucât `d < b` la un anumit moment memoria tampon devine goală. În
astfel de cazuri în derularea filmului intervine o pauză; în memoria
tampon se încarcă următorul fragment al filmului video; cum memoria
tampon este plină, din nou se începe reproducerea fragmentului încărcat
ș.a.m.d..

5. Programul reproduce ultimul fragment de film chiar și atunci când el
conține și mai puțin de «s» octeți.

Evident, pentru o vizionare cât mai plăcută, Păcală ar dori ca numărul
de pauze să fie minim, iar durata totală a pauzelor să nu depășească
valoarea «p» (incluzând și intervalul de timp necesar pentru încărcarea
primului fragment de film).
În acest scop el încearcă să schimpe capacitatea «s» a memoriei tampon.


### Cerință

Elaborați un program care, cunoscând durata «t» a filmului video,
parametrii «b», «d» și durata total admisibilă a pauzelor «p»,
calculează o astfel de capacitate «s» a memoriei tampon pentru care
numărul de pauze va fi minim.

În scopuri didactice, se consideră că timpul și cantitățile de
informație sunt mărimi continue sau, prin alte cuvinte, sunt admise
și părți fracționare de secundă și octet.


### Date de intrare

Fișierul text `video.in` conține pe prima linie numerele întregi
`d b t p` separate prin spațiu.


### Date de ieșire

Fișierul text `video.out` va conține pe o singură linie numărul întreg `s`.
Dacă există mai multe soluții, în fișierul de ieșire se va scrie cea mai
mică valoare a lui «s».

    Exemplul nr. 1
    --------------
    [video.in]                            [video.out]
    1024 2048 100 20                      20480

    Exemplul nr. 2
    --------------
    [video.in]                            [video.out]
    1024 2048 90 20                       18432

    Exemplul nr. 3
    --------------
    [video.in]                            [video.out]
    1024 1025 1 1                         1


### Restricții și precizări

* `1024 ≤ d ≤ 1073741823`
* `d < b ≤ 1073741824`
* `1 ≤ p ≤ 3600`
* `1 ≤ t ≤ 14400`
