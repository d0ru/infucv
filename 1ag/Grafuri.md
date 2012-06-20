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

_Propoziție:_ `∑d(xk) = 2·|E|, k=1..n` pentru orice graf.

_Corolar:_ în orice graf există un număr par de vârfuri de grad impar.

Se numește **secvență grafică** un șir de numere naturale d1,d2,..dn cu proprietatea că ele reprezintă gradele vârfurilor unui graf neorientat.

Un **lanț** L=[v0,v1,..vm] este o succesiune de vârfuri adiacente, iar «m» este **lungimea** lanțului.
Dacă vârfurile v0,v1,..vm sunt distincte două câte două, lanțul se numește **elementar**.
Dacă toate muchiile sunt distincte două câte două, lanțul se numește **simplu**.

În literatura grafurilor se întâlnesc noțiunile echivalente: _cale_, _drum_, _parcurs_.

Un **ciclu** este un lanț care se închide (v0=vm).

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

Aceste liste de adiacență pot fi implementate prin vectori (cap-listă), liste simple sau dublu înlănțuite.

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

_Proprietate:_ o muchie nu este critică dacă face parte din cel puțin un ciclu elementar al grafului.

La parcurgerea în adâncime a unui graf, muchiile sunt clasificate în două categorii:

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

**Lanț eulerian** este un lanț simplu ce [conține toate muchiile grafului][eulerian].

[eulerian]: http://en.wikipedia.org/wiki/Eulerian_path

**Ciclu eulerian** este un ciclu simplu (v0=vm) ce conține toate muchiile grafului ↦ **graf eulerian**.

_Teoremă:_ un graf conex este **eulerian** dacă și numai dacă gradul fiecărui vârf este **par**.

_Teoremă:_ un graf conex G are un **lanț eulerian** dacă și numai dacă există exact **două** vârfuri în G al căror grad să fie **impar**.

_Corolar:_ un graf conex este **eulerian** dacă și numai dacă mulțimea muchiilor sale poate fi descompusă în cicluri disjuncte.

_Teoremă:_ un graf conex G=(V,E) cu «2k» vârfuri de grad impar `k ≥ 1` are «k» lanțuri ale căror mulțimi de muchii formează o partiție a lui E, din care cel mult unul are lungime impară.


Grafuri hamiltoniene
--------------------

**Lanț hamiltonian** este un lanț elementar ce [trece prin toate vârfurile grafului][hamiltonian].

[hamiltonian]: http://en.wikipedia.org/wiki/Hamiltonian_path

**Ciclu hamiltonian** este un ciclu elementar (v0=vm) ce trece prin toate vârfurile grafului ↦ **graf hamiltonian**.

    δ(G) = min {d(u) | u ∈ V}
    Δ(G) = max {d(u) | u ∈ V}

_Lemă:_ fie G=(V,E) un graf neorientat și fie «u» și «v» două vârfuri neadiacente a.î. `d(u)+d(v) ≥ n`. Atunci G este hamiltonian ⇔ G+[u,v] este hamiltonian.

_Teoremă:_ un graf G=(V,E) este hamiltonian dacă `δ(G) ≥ n/2`.

_Teoremă:_ un graf G=(V,E) este hamiltonian dacă ∀u,v ∈ V distincte și neadiacente avem `d(u)+d(v) ≥ n`.

_Teoremă:_ fie G=(V,E) un graf neorientat și d1,d2..dn o secvență grafică. Dacă `∀k a.î. dk ≤ k ≤ n/2 ⇒ d[n-k] ≥ n-k` atunci graful este hamiltonian.

**Închiderea lui G** notată cu `cl(G)` este un graf construit prin adăugarea tuturor muchiilor `(u,v)`, ∀u,v ∈ V distincte și neadiacente a.î. `d(u)+d(v) ≥ n`.

_Lemă:_ orice graf are o singură închidere.

_Corolar:_ un graf G=(V,E) este hamiltonian dacă `cl(G) ≅ Kn` (închiderea lui G este izomorfă cu graful complet de ordinul «n»).

O mulțime de vârfuri A este **independentă** dacă oricare două elemente distincte din A sunt independente. Numărul de independență a lui G notat `β(G) = |I|`, unde I este o mulțime independentă pe G cu cel mai mare număr de vârfuri.

   β(G) = 1 dacă și numai dacă graful G este complet

O **tăietură** este o submulțime U a lui V a.î. G-U să fie neconex. Conectivitatea lui G notată `κ(G)` reprezintă numărul minim de puncte ale unei tăieturi.

_Teoremă:_ un graf G=(V,E) cu ordinul `n ≥ 3` este hamiltonian dacă `κ(G) ≥ β(G)`.


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

* parcurgere în **preordine**: rădăcină, subarbore stâng, subarbore drept

Exemplu: 1 2 3 4 5 6 7 8 9

* parcurgere în **inordine**: subarbore stâng, rădăcină, subarbore drept

Exemplu: 3 4 2 6 5 7 1 8 9

* parcurgere în **postordine**: subarbore stâng, subarbore drept, rădăcină

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


### Arbori binari de căutare

Un **arbore binar de căutare** este un arbore binar în care orice vârf «i» are proprietatea:

* `inf[i] ≥ inf[j]` pentru toate vârfurile «j» ce aparțin subarborelui binar stâng

* `inf[i] ≤ inf[j]` pentru toate vârfurile «j» ce aparțin subarborelui binar drept

Am notat cu `inf[i]` informația asociată vârfului «i» — un tip de date peste care avem o relație de ordine.

Prin parcurgerea înordine a unui arbore binar de căutare se obțin elementele vectorului «inf[i]» în ordine crescătoare.
Operațiile de *creare* a arborelui, *ștergere*, *modificare* sau *inserare* a unui nod se mod face într-un mod optim astfel încât să fie păstrată proprietatea de *arbore de căutare*.


Arbori oarecare
---------------

Numim **arbore** o mulțime finită de noduri astfel încât:

1) există un nod special numit rădăcina arborelui

2) celelalte noduri sunt repartizate în «n» mulțimi disjuncte două câte două `A1,A2..An`, fiecare mulțime `Ai` constituind la rândul ei un arbore.

### Moduri de reprezentare

Un exemplu de arbore oarecare:

             (1)
           /  |   \
        (2)  (3)    (.....4.....)
             / \    /   /   \   \
           (5) (6) (7) (8) (9) (10)

1) legături fiu-frate: `fiu[k]` este primul descendent al nodului «k», `frate[fiu[k]]` este următorul descendent al tatălui nodului «k».

      nod | 1 2 3 4 5 6 7 8 9 10
    ------|---------------------
      fiu | 2 0 5 7 0 0 0 0 0  0
    frate | 0 3 4 0 6 0 8 9 10 0

2) lista descendenților (sau cap-listă)

      nod | 1 2 3 4 5 6 7 8 9 10
    ------|---------------------
      cap | 1 0 4 6 0 0 0 0 0  0

       (2 3 4 5 6 7 8 9  10)
       (2 3 0 5 0 7 8 10  0)

3) reprezentarea de tip tată

     nod | 1 2 3 4 5 6 7 8 9 10
    -----|---------------------
    tată | 0 1 1 1 3 3 4 4 4  4

### Metode de parcurgere

* parcurgere în **apreordine**: rădăcină, subarbori

Exemplu: 1  2  3 5 6  4 7 8 9 10

* parcurgere în **apostordine**: subarbori, rădăcină

Exemplu: 2  5 6 3  7 8 9 10 4  1

### Arbori de acoperire de cost minim

Fie `G=(V,E)` un graf neorientat. Se cere să se determine un *graf parțial connex* `Gc=(V,Ep)` cu `Ep ⊆ E` cu proprietatea că suma costurilor tuturor muchiilor este minimă. Graful parțial de cost minim este un arbore, de aceea se mai numește *arbore parțial de cost minim*.

Algoritmii de căutare a arborelui de acoperire de cost minim face abstracție de forma de reprezentare a grafului neorientat.

### Algoritmul lui Prim

Se pornește cu o mulțime formată dintr-un singur nod. La fiecare pas se alege muchia de cost minim cu o sigură extremitate în mulțimea virtuală M.
Procesul se încheie după `n - 1` pași. Sunt utilizați trei vectori de dimeniune `n = |V|`:

* `vizitat[]`

* `dist[]` va conține distanța minimă de la nodul `v ∉ M` la un nod `u ∈ M` (inițial egal cu `cost[nod,v]`)

* `tata[]` va conține pentru fiecare nod `v ∉ M` nodul `u ∈ M` a.î. `cost[u,v] = minim {cost[k,v] | ∀k ∈ M}`

Algoritmul lui Prim implementat simplu are o complexitate O(N²), implementat cu *heap*-uri Fibonacii (sau *pairing heaps*) are o complexitate O(M•lgN).

    procedura ARBORE_COST_MINIM_PRIM2(graf, nr, nod, L)
      INTRARE: graf — graful conex neorientat
               nr — numărul de vârfuri sau
                  — numărul de muchii (pentru reprezentarea MM)
               nod — vârful de pornire

      for k ← 1,n do
        vizitat[k] ← false             // M ← ∅
        dist[k] ← cost[nod,k]          // vectorul distanțelor
        tata[k] ← nod
      sfârșit «for»
      vizitat[nod] ← true              // M ← { nod }
      L ← ∅                            // mulțimea muchiilor ce formează arborele de cost minim

      for i ← 1,nr-1 do
        u ← minim {dist[u] | u ∈ V\M}
        vizitat[u] ← true              // M ← M ∪ {u}
        L ← (tata[u],u)                // muchie adăugată în listă

        // actualizare distanțe după introducerea nodului «u» în arbore
        for (toți vecinii «v» ai lui «u», v ∈ V\M)
          if (!vizitat[v] && dist[v] > cost[u,v])
            dist[v] ← cost[u,v]
            tata[v] ← u
          sfârșit «if»
        sfârșit «for»
      sfârșit «for»
    sfârșit procedură

### Algoritmul lui Kruskal

Se pornește cu o pădure de arbori, fiecare arbore fiind având un singur nod.
La fiecare pas se alege o muchie de cost minim. Se verifică dacă extremitățile fac parte din arbori diferiți, în caz afirmativ muchia este selectată și cei doi arbori parțiali sunt uniți.

La fiecare pas numărul arborilor parțiali scade cu 1. Procesul se încheie după `n - 1` pași.

    procedura ARBORE_COST_MINIM_KRUSKAL2(graf, nr, nod, L)
      INTRARE: graf — graful conex neorientat
               nr — numărul de vârfuri sau
                  — numărul de muchii (pentru reprezentarea MM)
               nod — vârful de pornire

      for k ← 1,n do
        inițializare_arbore(k)
      sfârșit «for»
      cost ← 0                         // costul total
      L ← ∅                            // mulțimea muchiilor ce formează arborele de cost minim

      sortează crescător muchiile în funcție de cost
      for i ← 1,nr-1 do
        selectează următoarea muchie (u,v) de cost minim
        if (nodurile u,v NU sunt în același arbore parțial)
          cost ← cost + cost[u,v]
          L ← L ∪ {(u,v)}              // muchie adăugată în listă
          unește arborii ce conțin nodurile «u» și «v»
        sfârșit «if»
      sfârșit «for»
    sfârșit procedură

O implementare mai detaliată construiește matricea muchiilor formată din 3 coloane, ultima reprezentând costul muchiei asociate. Această matrice este ordonată crescător după cea de-a treia coloană (cost).


Grafuri orientate
-----------------

Se numește **graf orientat** o pereche ordonată G = (V,E), unde V este o mulțime de vârfuri sau noduri, iar E este o mulțime de arce.

Noțiunea de *muchie* este înlocuită cu noțiunea de *arc*. O pereche de noduri (x,y) este ordonată, adică `(x,y) ≠ (y,x)`. Se mai spune că vârfurile x și y sunt adiacente.

**Gradul exterior** al unui vârf (eng. "degree") notat d+(x) este egal cu numărul arcelor care pornesc din «x».
**Gradul interior** al unui vârf notat d-(x) este egal cu numărul arcelor cu săgeata pe «x».

Un **lanț** L=[l1,..lm] este o succesiune de *arce* cu proprietatea că oricare două arce consecutive ale secvenței au o extremitate comună.

Un **drum** (eng. "path") D=[v0,v1,..vm] este o [succesiune de *vârfuri*][path] cu proprietatea că oricare două vârfuri consecutive ale secvenței formează un arc.
Dacă vârfurile v0,v1,..vm sunt distincte două câte două, drumul se numește **elementar**.

[path]: http://en.wikipedia.org/wiki/Path_(graph_theory)

Un **ciclu** este un [drum care se încheie][cycle] (v0=vm).
Pentru a sublinia diferența față de grafurile neorientate, un ciclu al unui graf orientat se mai numește **circuit**.

[cycle]: http://en.wikipedia.org/wiki/Cycle_(graph_theory)

Un graf este **conex** dacă pentru orice pereche de vârfuri *x* și *y* există un *lanț*.
Un graf este **tare conex** dacă între orice pereche de vârfuri *x* și *y* există un *drum*.

### Parcurgerea grafurilor

Pentru fiecare nod *v* vom introduce două numere: prenum[v], postnum[v].

* `prenum[v]` — momentul pentru care este întâlnit nodul *v* pentru prima oară

* `postnum[v]` — momentul în care prelucrarea nodului *v* s-a încheiat

La parcurgerea unui graf orientat avem următoarele tipuri de arce:

* arc al arborelui de acoperire

        prenum[u] < prenum[v]
        postnum[u] > postnum[v]

* arc de înaintare (u,v) — dacă este paralel cu un drum de la *u* la *v* din arborele de acoperire

        prenum[u] < prenum[v]
        postnum[u] > postnum[v]

* arc de întoarcere — arcul (u,v) are sens contrar unui drum de la *v* la *u* din arborele de acoperire

        prenum[u] > prenum[v]
        postnum[u] < postnum[v]

* arc de traversare (u,v) — dacă *v* nu este descendent direct, nici strămoș al lui *u*

        prenum[u] > prenum[v]
        postnum[u] > postnum[v]
