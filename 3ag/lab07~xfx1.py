#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test de încrucișare aleatoare a unor
cromozomi selectați aleator folosind metoda ruletei.
"""

import crmz
import pcrmz
from numpy import sin


def fx1(x):
    return -sin(x) / x

a1, b1 = -4, 4
xmin = -3.55271368e-15
fx1min = fx1(xmin)

def adecv(cr):
    """ Funcția de adecvare asociată funcției fx1 """
    x1 = cr.getv(1)
    return 1. / abs(fx1min - fx1(x1))

def main():
    m = 10      # dimensiune populație
    popu = pcrmz.PCrmz()
    # inițializare populație
    for i in range(m):
        popu.cr.append(crmz.CrmzCR(pr = 4))
        popu.cr[-1].reset( (a1, b1, '') )

    # afișare populație
    print('Cromozomi generați automat:')
    for c in popu.cr:
        x1 = c.getv(1)
        print('%2d: %s, coeficient de adecvare %f, f(%.3f)=%f' % (c.id, c.sir(), adecv(c), x1, fx1(x1)))

    print('')
    print('gen #0: încrucișări ..')
    popu.xbin(adecv, info=True)


if __name__ == '__main__':
    main()
