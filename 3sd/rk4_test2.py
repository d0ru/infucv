#!/usr/bin/env python
# -*- coding: utf-8 -*-

from rungekutta import rk4pasfix
from math import exp, sqrt

# I.CATANA
def yp(y, t):
    """ derivata parțială de ordinul I """
    return y - t**2 + 1

def y(t):
    """ soluția exactă calculată analitic """
    return t**2 + 2*t + 1 - exp(t)/2.0


def main():
    y0, t0, tmax = 0.5, 0.0, 2.0
    for dt, pasi in zip([0.5, 0.2, 0.05], [1, 2, 10]):
        (yn, tn) = rk4pasfix(yp, y0, t0, dt, tmax)
        print ("  t   | Soluția numerică  | Soluția analitică | Eroare (Δt = %g)" % dt)
        print ('-' * 66)
        for i in range(0, len(tn), pasi):
            wn = y(tn[i])
            print (" %2.2f | %5.15f | %5.15f | %5.15f" % (tn[i], wn, yn[i],
                                                          abs(yn[i] - wn)))
        print('')

if __name__ == '__main__':
    main()
