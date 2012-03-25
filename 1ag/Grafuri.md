Grafuri neorientate
-------------------

Se numește **graf** o pereche ordonată G = (V,E),
V = {x1, x2, ..., xn}, E ⊆ VxV, E = {(x,y)| x,y ∈ V}.

Elemente xi ∈ V se numesc **noduri** sau **vârfuri**.
Elementele mulțimii E sunt **arce** sau **muchii**.

|V| se numește **ordinul** grafului G (numărul vârfurilor), iar |E| se numește **dimensiunea** grafului G (numărul muchiilor).

Kn se numește **graf complet** de ordinul «n» un graf cu proprietatea că oricare două vârfuri distincte sunt adiacente.

Gp=(V,Ep) se numește **graf parțial** al unui graf G=(V,E) dacă Ep ⊆ E.

S=(Vp,Ep) se numește **subgraf** al lui G=(V,E) dacă Vp ⊆ V iar muchiile din Ep sunt toate muchiile din E care au ambele extremități în mulțimea Vp.

**Gradul** unui vârf notat d(x) este egal cu numărul muchiilor incidente cu vârful «x». Un vârf cu gradul 0 se numește **vârf izolat**.

Propoziție: Pentru orice graf ∑d(xk) = 2·|E|, k=1..n.

Se numește **secvență grafică** un șir de numere naturale d1,d2,..dn cu proprietatea că ele reprezintă gradele vârfurilor unui graf neorientat.

Un **lanț** L=[v0,v1,..vm] este o succesiune de vârfuri adiacente, iar «m» este **lungimea** lanțului. Dacă vârfurile v0,v1,..vm sunt distincte două câte două, lanțul se numește **elementar**.

**Ciclul** este un lanț care se încheie (v0=vm).

**Ciclu Hamiltonian** este un ciclu elementar ce trece prin toate vârfurile grafului ↦ graf Hamiltonian.

**Lanț Eulerian** este un lanț ce nu se repetă (conține fiecare muchie doar o singură dată). Dacă în plus v0=vm avem un **ciclu Eulerian** într-un graf Eulerian.

Un **graf conex** este un graf fără componente izolate, adică pentru orice pereche de vârfuri există un lanț de legătură.

Se numește **componentă conexă** un subgraf conex maximal. Orice graf neconex se împarte în două sau mai multe componente conexe.
