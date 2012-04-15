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


## Grafuri euleriene

**Lanț eulerian** este un lanț ce nu se repetă (conține fiecare muchie o singură dată). Dacă în plus `v0=vm` avem un **ciclu eulerian** ↦ **graf eulerian**.

Teoremă: un graf conex este eulerian dacă și numai dacă gradul fiecărui vârf este par.

Teoremă: un graf conex G are un lanț eulerian dacă și numai dacă există exact două vârfuri în G al căror grad să fie impar.

Corolar: un graf conex este eulerian dacă și numai dacă mulțimea muchiilor sale poate fi descompusă în cicluri disjuncte.

Teoremă: un graf conex G=(V,E) cu «2k» vârfuri de grad impar (k ≥ 2) are «k» lanțuri ale căror mulțimi de muchii formează o partiție a lui E, din care cel mult unul are lungime impară.


## Grafuri hamiltoniene

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
