# -*- coding: utf-8 -*-

"""
Metoda Runge-Kutta de aproximare a soluțiilor unei ecuații diferențiale.
  http://rosettacode.org/wiki/Runge-Kutta_method
  http://mathworld.wolfram.com/Runge-KuttaMethod.html
"""

def rk4(yderiv1, yn, tn, dt):
    """
    Metoda Runge-Kutta de ordinul 4 — o singură iterație.
    - yderiv1(y, t): funcția derivată de ordinul I al funcției „y(t)”
    - (yn, tn): valorile calculate la pasul N, inițial (y0, t0)
    - dt: pasul de timp (Δt)

    Implementarea face abstracție de forma de reprezentare a valorii
    „yn” ce a fost calculată la pasul N (ex. valoare, vector NumPy).

    Returnează un tuplu de forma (yn_urm, tn_urm), unde:
    - yn_urm: valoarea aproximativă a funcției „y(t)” la pasul N+1
    - tn_urm: pasul de timp asociat valorii „yn_urm” la pasul N+1
    """
    dy1 = dt * yderiv1(yn,           tn)
    dy2 = dt * yderiv1(yn + dy1/2.0, tn + dt/2.0)
    dy3 = dt * yderiv1(yn + dy2/2.0, tn + dt/2.0)
    dy4 = dt * yderiv1(yn + dy3,     tn + dt)
    yn_urm = yn + (dy1 + 2*dy2 + 2*dy3 + dy4) / 6.0
    tn_urm = tn + dt
    return (yn_urm, tn_urm)


def rk4pasfix(yderiv1, y0, t0, dt, tmax):
    """
    Metoda Runge-Kutta de ordinul 4 cu pas fix.
    - yderiv1(y, t): funcția derivată de ordinul I al funcției „y(t)”
    - (y0, t0): valorile inițiale la pasul 0 — „y(t0)”
    - dt: pasul de timp fix (Δt)
    - [t0, tmax]: intervalul pe care este definită funcția necunoscută

    Implementarea face abstracție de forma de reprezentare a valorii
    inițiale „y0” (ex. valoare numerică simplă, vector NumPy).

    Returnează un tuplu de forma (yn, tn), unde:
    - yn: o listă cu toate valorile funcției „y(t)” calculate cu RK4
    - tn: o listă cu pașii de timp asociați valorilor din lista „yn”
    """
    yn, tn = [y0], [t0]
    yn_urm, tn_urm = y0, t0
    nrpasi = int((tmax - t0) / dt)
    for n in range(nrpasi):
        (yn_urm, tn_urm) = rk4(yderiv1, yn_urm, tn_urm, dt)
        yn.append(yn_urm)
        tn.append(tn_urm)
    return (yn, tn)
