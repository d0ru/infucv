Algoritmica Grafurilor
======================


Grafuri neorientate
-------------------

Se numește **graf** o pereche ordonată G = (V,E :: eng. [Vertices,Edges][1]), V = {x1, x2, ..., xn}, E ⊆ VxV, E = {(x,y)| x,y ∈ V}.

[1]: http://en.wikipedia.org/wiki/Graph_(mathematics)

Elemente xi ∈ V se numesc **noduri** sau **vârfuri**.
Elementele mulțimii E sunt **arce** sau **muchii**.

|V| se numește **ordinul** grafului G (numărul vârfurilor), iar |E| se numește **dimensiunea** grafului G (numărul muchiilor).

Kn se numește **graf complet** de ordinul «n» un graf cu proprietatea că oricare două vârfuri distincte sunt adiacente.

Gp=(V,Ep) se numește **graf parțial** al unui graf G=(V,E) dacă `Ep ⊆ E`.

S=(Vp,Ep) se numește **subgraf** al lui G=(V,E) dacă `Vp ⊆ V` iar muchiile din Ep sunt toate muchiile din E care au ambele extremități în mulțimea Vp.

**Gradul** unui vârf (eng. "degree") notat d(x) este egal cu numărul muchiilor incidente cu vârful «x». Un vârf cu gradul 0 se numește **vârf izolat**.

Propoziție: `∑d(xk) = 2·|E|, k=1..n` pentru orice graf.

Se numește **secvență grafică** un șir de numere naturale d1,d2,..dn cu proprietatea că ele reprezintă gradele vârfurilor unui graf neorientat.

Un **lanț** L=[v0,v1,..vm] este o succesiune de vârfuri adiacente, iar «m» este **lungimea** lanțului. Dacă vârfurile v0,v1,..vm sunt distincte două câte două, lanțul se numește **elementar**.

**Ciclul** este un lanț care se încheie (v0=vm).

Un **graf conex** este un graf fără componente izolate, adică între oricare două vârfuri există un lanț.

Se numește **componentă conexă** un subgraf conex maximal. Orice graf conex are o singură componentă conexă. Orice graf neconex se împarte în două sau mai multe componente conexe.

### Moduri de reprezentare

1) *Matricea de adiacență* este o matrice `A ∈ M[n×n]` unde `n = |V|` iar `a[i,j] = 1` dacă există o muchie între nodurile «i» și «j», sau `a[i,j] = 0` în caz contrar. Pentru un graf neorientat această matrice este simetrică.

2) *Matricea costurilor* reprezintă o variație a matricei de adiacență în care fiecare muchie are un cost `d > 0`.
Valorile matricii se definesc astfel:

* `a[i,i] = 0`

* `a[i,j] = d` dacă muchia `[i,j] ∈ E`

* `a[i,j] = ±∞` dacă muchia `[i,j] ∉ E`

3) *Liste de adiacență* — sau liste de vecini, pentru fiecare nod se construiește lista nodurilor adiacente.
Pentru un graf neorientat numărul elementelor din listele de vecini este `2 × |E|` deoarece orice muchie [u,v] va fi prezentă atât în lista nodului «u» cât și cea a nodului «v».

Aceste liste de adiacență pot fi implementate prin vectori (CAP+LISTA), liste simple sau dublu înlănțuite.

4) *Lista de muchii* — sau matricea de muchii — într-o matrice `2 x |E|` sunt reținute toate muchiile [u,v], pe prima linie este «u» iar pe a doua linie este «v».

### Parcurgerea grafurilor

1) Parcurgerea în lățime

Metoda de *parcurgere în lățime* prelucrează nodurile grafului în felul următor:

* este prelucrat nodul de pornire

* sunt prelucrați toți vecinii încă nevizitați ai acestuia

* se reia algoritmul cu vecinii încă nevizitați ai acestora

Algoritmul de parcurgere în lățime face abstracție de forma de reprezentare a grafului neorientat.

    procedura PARCURGERE_LĂȚIME(graf, nr, nod)
      INTRARE: graf — graful neorientat
               nr — numărul de vârfuri sau
                  — numărul de muchii (pentru reprezentarea MM)
               nod — vârful de pornire

      for i ← 1,n do
        vizitat[i] ← false
      sfârșit «for»
      prelucrează_nod(nod)
      vizitat[nod] ← true

      Q ← nod                    // adaugă nod în coadă
      while (Q ≠ ∅)
        u ← Q                    // extrage nod din coadă

        // prelucrează toți vecinii nodului «u»
        for (toți vecinii «v» ai lui «u»)
          if (!vizitat[v])
            prelucrează_nod(v)
            vizitat[v] ← true
            Q ← v
        sfârșit «for»
      sfârșit «while»
    sfârșit procedură

2) Parcurgerea în adâncime

Metoda de *parcurgere în adâncime* prelucrează nodurile grafului în felul următor:

* este prelucrat nodul de pornire

* este prelucrat primul vecin încă nevizitat al acestuia

* este prelucrat primul vecin încă nevizitat al celui prelucrat anterior

* se merge în adâncime când se ajunge la un nod frunză sau pentru care toți vecinii săi au fost vizitați

* se reia algoritmul cu nodul părinte al ultimului nod vizitat

Algoritmul de parcurgere în adâncime face abstracție de forma de reprezentare a grafului neorientat.

    procedura PARCURGERE_ADÂNCIME(graf, nr, nod)
      INTRARE: graf — graful neorientat
               nr — numărul de vârfuri sau
                  — numărul de muchii (pentru reprezentarea MM)
               nod — vârful de pornire

      for i ← 1,n do
        vizitat[i] ← false
      sfârșit «for»
      prelucrează_nod(nod)
      vizitat[nod] ← true

      S ← nod                    // adaugă nod în stivă
      găsit ← false
      while (S ≠ ∅)
        if (!găsit)
          u ← S                  // extrage nod din stivă

        găsit ← false
        // prelucrează primul vecin nevizitat al nodului «u» (dacă există)
        for (toți vecinii «v» ai lui «u»)
          if (!vizitat[v])
            prelucrează_nod(v)
            vizitat[v] ← true
            găsit ← true
            if («v» nu este ultimul vecin al nodului «u»)
              S ← u
            u ← v                // pasul de continuare a buclei «while»
            break                // întrerupe bucla «for»
        sfârșit «for»
      sfârșit «while»
    sfârșit procedură

### Muchie critică

O muchie este **critică** dacă prin eliminarea ei va crește numărul de componente conexe ale grafului.

Proprietate: o muchie nu este critică dacă face parte din cel puțin un ciclu elementar al grafului.

Muchiile unui graf sunt clasificate în două categorii:

* muchie a arborelui de acoperire

* muchie de întoarcere — nu face parte din arborele de acoperire

Vectorul `pasu[]` reprezintă pasul la care un nod este vizitat.
Vectorul `mini[]` este calculat pentru fiecare nod cu formula:

                     / pasu[u] 
    mini[u] = minim ⟨  pasu[i] pentru ∀i: [u,i] este muchie de întoarcere
                     \ mini[v] pentru ∀v descendent direct al lui «u»

Algoritmul de căutare a muchiilor critice face abstracție de forma de reprezentare a grafului neorientat.

    procedura MUCHII_CRITICE(graf, nr, nod)
      INTRARE: graf — graful neorientat
               nr — numărul de vârfuri sau
                  — numărul de muchii (pentru reprezentarea MM)
               nod — vârful de pornire

      // I: prima parcurgere construiește vectorii pasu[] și mini[]
      for k ← 1,n do
        vizitat[k] ← false
      sfârșit «for»
      vizitat[nod] ← true
      contuar ← 1
      tata[nod] ← 0
      pasu[nod] ← 1              // pasul la care a fost vizitat nodul «u»
      mini[nod] ← 1              // minumul calculat pentru nodul «u»

      S ← nod                    // adaugă nod în stivă
      găsit ← false
      while (S ≠ ∅)
        if (!găsit)
          u ← S                  // extrage nod din stivă

        găsit ← false
        for (toți vecinii «v» ai lui «u»)
          if (!vizitat[v])       // primul vecin nevizitat al nodului «u»
            tata[v] ← u
            contuar ← contuar + 1
            pasu[v] ← contuar,  mini[v] ← contuar
            vizitat[v] ← true
            găsit ← true
            S ← u
            u ← v                // pasul de continuare a buclei «while»
            break                // întrerupe bucla «for»
          sfârșit «if»

          // "else" muchie de întoarcere?
          if ((tata[u] ≠ v) && (mini[u] > pasu[v]))
            mini[u] ← pasu[v]
            // actualizare valoare mini[] pentru părinte și strămoși
            for (k ← tata[u]; mini[k] > mini[u]; k ← tata[k])
              mini[k] ← mini[u]
          sfârșit «if»
        sfârșit «for»
      sfârșit «while»

      // II: a doua parcurgere în adâncime afișează muchiile critice
      for k ← 1,n do
        vizitat[k] ← false
      sfârșit «for»
      vizitat[nod] ← true

      S ← nod
      găsit ← false
      while (S ≠ ∅)
        if (!găsit)
          u ← S

        găsit ← false
        for (toți vecinii «v» ai lui «u»)
          if (!vizitat[v])
            if (pasu[u] < mini[v])
              Output { "Muchia [u,v] este critică" }
            vizitat[v] ← true
            găsit ← true
            if («v» nu este ultimul vecin al nodului «u»)
              S ← u
            u ← v
            break
        sfârșit «for»
      sfârșit «while»
    sfârșit procedură


Grafuri euleriene
-----------------

**Lanț eulerian** este un lanț ce nu se repetă (conține fiecare muchie o singură dată). Dacă în plus `v0=vm` avem un **ciclu eulerian** ↦ **graf eulerian**.

Teoremă: un graf conex este un **graf eulerian** dacă și numai dacă gradul fiecărui vârf este **par**.

Teoremă: un graf conex G are un **lanț eulerian** dacă și numai dacă există exact **două** vârfuri în G al căror grad să fie **impar**.

Corolar: un graf conex este **eulerian** dacă și numai dacă mulțimea muchiilor sale poate fi descompusă în cicluri disjuncte.

Teoremă: un graf conex G=(V,E) cu «2k» vârfuri de grad impar (k ≥ 1) are «k» lanțuri ale căror mulțimi de muchii formează o partiție a lui E, din care cel mult unul are lungime impară.


Grafuri hamiltoniene
--------------------

**Lanț hamiltonian** este un lanț ce trece o singură dată prin toate vârfurile unui graf.

**Ciclu hamiltonian** este un ciclu elementar (v0=vm) ce trece prin toate vârfurile grafului ↦ **graf hamiltonian**.

    δ(G) = min {d(u) | u ∈ V}
    Δ(G) = max {d(u) | u ∈ V}

Lemă: fie G=(V,E) un graf neorientat și fie «u» și «v» două vârfuri neadiacente a.î. `d(u)+d(v) ≥ n`. Atunci G este hamiltonian ⇔ G+[u,v] este hamiltonian.

Teoremă: un graf G=(V,E) este hamiltonian dacă `δ(G) ≥ n/2`.

Teoremă: un graf G=(V,E) este hamiltonian dacă ∀u,v ∈ V distincte și neadiacente avem `d(u)+d(v) ≥ n`.

Teoremă: fie G=(V,E) un graf neorientat și d1,d2..dn o secvență grafică. Dacă `∀k a.î. dk ≤ k ≤ n/2 ⇒ d[n-k] ≥ n-k` atunci graful este hamiltonian.

**Închiderea lui G** notată cu `cl(G)` este un graf construit prin adăugarea tuturor muchiilor `(u,v)`, ∀u,v ∈ V distincte și neadiacente a.î. `d(u)+d(v) ≥ n`.

Lemă: orice graf are o singură închidere.

Corolar: un graf G=(V,E) este hamiltonian dacă `cl(G) ≅ Kn` (închiderea lui G este izomorfă cu graful complet de ordinul «n»).

O mulțime de vârfuri A este **independentă** dacă oricare două elemente distincte din A sunt independente. Numărul de independență a lui G notat `β(G) = |I|`, unde I este o mulțime independentă pe G cu cel mai mare număr de vârfuri.

   β(G) = 1 dacă și numai dacă graful G este complet

O **tăietură** este o submulțime U a lui V a.î. G-U să fie neconex. Conectivitatea lui G notată `κ(G)` reprezintă numărul minim de puncte ale unei tăieturi.

Teoremă: un graf G=(V,E) cu ordinul `n ≥ 3` este hamiltonian dacă `κ(G) ≥ β(G)`.


Arbori binari
-------------

Un **arbore liber** este un graf G = (V,E) neorientat, conex și aciclic.
Propriețăți ale arborilor liberi:

* între oricare două vârfuri din V există un drum elementar unic

* toate muchiile din E sunt critice

* `|E| = |V| - 1`

* graful obținut prin adăugarea unei muchii oarecare conține un ciclu

Lungimea drumului de la rădăcină la un vârf se numește **adâncimea** vârfului.
Toate vârfurile ce au aceeași adâncime se spune că sunt pe același nivel.

Lungimea celui mai lung drum de la rădăcină la o frunză este **înălțimea arborelui**.
Nivelul unui vârf se determină ca diferența dintre înălțimea arborelui și adâncimea acestui vârf.

Un **arbore binar** este un arbore cu rădăcină în care fiecare vârf are cel mult doi descendenți: stâng, drept.
Arborele binar fără vârfuri se numește **arbore vid** sau **arbore nul**.

### Moduri de reprezentare

Un exemplu de arbore binar:

            (1)
           /   \
        (2)     (8)
       /   \       \
    (3)     (5)     (9)
      \     / \
      (4) (6) (7)

1) expresii cu paranteze: (radăcina (arborele stâng, arborele drept)).

Un arbore cu un singur vârf «r» se reprezintă astfel: (r (0, 0)).
Exemplu: (1 ((2 (3 (0, 4))), (5 (6, 7))), (8 (0,9)))).

2) forma standard

      nod | 1 2 3 4 5 6 7 8 9
    ------|------------------
    stâng | 2 3 0 0 6 0 0 0 0
    drept | 8 5 4 0 7 0 0 9 0

3) reprezentarea de tip tată

     nod | 1 2 3 4 5 6 7 8 9
    -----|------------------
    tată | 0 1 2 3 2 5 5 1 8

### Metode de parcurgere

În toate metodele este parcurs mai întâi subarborele stâng și apoi subarborele drept.

* parcurgere în **preordine**: rădăcină, subarbore stâng, subarbore drept.

Exemplu: 1 2 3 4 5 6 7 8 9

* parcurgere în **inordine**: subarbore stâng, rădăcină, subarbore drept.

Exemplu: 3 4 2 6 5 7 1 8 9

* parcurgere în **postordine**: subarbore stâng, subarbore drept, rădăcină.

Exemplu: 4 3 6 7 5 2 9 8 1

Algoritmul de parcurgere a arborelui se bazează pe parcurgerea în adâncime.
Am utilizat o stivă «S» în care sunt introduse nodurile parcurse în adâncime spre stânga pornind de la rădăcină. Atunci când nu se mai poate merge la stânga se reia algoritmul cu descendentul drept al nodului curent. Dacă acesta nu există, se continuă cu primul nod găsit în stivă.
Parcurgerea se termină în momentul în care stiva este vidă.

    procedura PARCURGERE_ARBORE_BINAR(rad, st[], dr[])
      for i ← 1,n do
        vizitat[i] ← false
      sfârșit «for»

      S ← rad                    // o structură de tip stivă
      while (S ≠ ∅)
        k ← S

        // parcurgere în adâncime
        while (0 ≠ st[k] && !vizitat[st[k]])
          prelucrează_nod(k)     // PRE
          vizitat[k] ← true      // PRE
          S ← k
          k ← st[k]
        sfârșit «while»

        // nod nevizitat?
        if (!vizitat[k])         // PRE+IN
          prelucrează_nod(k)     // PRE+IN
          vizitat[k] ← true      // PRE+IN

        // subarbore drept nevizitat?
        if (0 ≠ dr[k] && !vizitat[dr[k]])
          S ← k                  // POST
          S ← dr[k]
        else                     // POST
          prelucrează_nod(k);    // POST
          vizitat[k] ← true;     // POST
      sfârșit «while»
    sfârșit procedură


Arbori binari de căutare
------------------------

Un **arbore binar de căutare** este un arbore binar în care orice vârf «i» are proprietatea:

* `inf[i] ≥ inf[j]` pentru toate vârfurile «j» ce aparțin subarborelui binar stâng

* `inf[i] ≤ inf[j]` pentru toate vârfurile «j» ce aparțin subarborelui binar drept

Am notat cu `inf[i]` informația asociată vârfului «i» — un tip de date peste care avem o relație de ordine.

Prin parcurgerea înordine a unui arbore binar de căutare se obțin elementele vectorului «inf[i]» în ordine crescătoare.
Operațiile de *creare* a arborelui, *ștergere*, *modificare* sau *inserare* a unui nod se mod face într-un mod optim astfel încât să fie păstrată proprietatea de *arbore de căutare*.
