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


def rk4pasvar(yderiv1, y0, t0, dt0, tmax, delta = 0.000001):
    """
    Metoda Runge-Kutta de ordinul 4 cu pas variabil.
    - yderiv1(y, t): funcția derivată de ordinul I al funcției „y(t)”
    - (y0, t0): valorile inițiale la pasul 0 — „y(t0)”
    - dt0: pasul de timp inițial (Δt)
    - [t0, tmax]: intervalul pe care este definită funcția necunoscută
    - delta: eroarea de aproximare acceptată a sistemului RK4

    Implementarea face abstracție de forma de reprezentare a valorii
    inițiale „y0” (ex. valoare numerică simplă, vector NumPy).

    Returnează un tuplu de forma (yn, tn), unde:
    - yn: o listă cu toate valorile funcției „y(t)” calculate cu RK4
    - tn: o listă cu pașii de timp asociați valorilor din lista „yn”
    - en: o listă cu erorile asociate valorilor din lista „yn”
    """
    from numpy.linalg import norm
    yn, tn, en, dt = [y0], [t0], [0], dt0
    while tn[-1] < tmax:
        while True:
            (yn_urm, tn_urm)   = rk4(yderiv1, yn[-1],  tn[-1],  dt)
            (yn_urm1, tn_urm1) = rk4(yderiv1, yn[-1],  tn[-1],  dt/2.0)
            (yn_urm2, tn_urm2) = rk4(yderiv1, yn_urm1, tn_urm1, dt/2.0)
            er = norm(yn_urm2 - yn_urm) * 16. / 15.     # 2^r=16
            if 0 <= er <= 0.9 * delta:
                break
            else:
                dt *= (0.9 * delta / er) ** (1./5)      # 1/(r+1)

        yn_urm = yn_urm2 + (yn_urm2 - yn_urm) / 15.0    # 2^r - 1
        yn.append(yn_urm)
        tn.append(tn_urm)
        en.append(er)
        if er > 0:
            dt *= (delta / er) ** (1./4)                # 1/r
    return (yn, tn, en)
