#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program minimizare a unei funcții cu o singură
variabilă folosind algoritmi genetici.
"""

import crmz
import pcrmz
import numpy
import pylab
from scipy.optimize import fmin


# funcție cu o variabilă
def fx1(x):
    return -numpy.sin(x) / x

a1, b1 = -15, 15
#xmin = -3.55271368e-15
xmin = fmin(fx1, -4.)
#fx1min = -1.
fx1min = fx1(xmin)

def adecv(cr):
    """ Funcția de adecvare asociată funcției fx1 """
    x1 = cr.getv(1)
    return 1. / abs(fx1min - fx1(x1))

def main():
    m = 20      # dimensiune populație
    err = 0.0006

    popu = pcrmz.PCrmz()
    # inițializare populație
    for i in range(m):
        popu.cr.append(crmz.CrmzCR(pr=4))
        popu.cr[-1].reset( (a1, b1, '') )

    # afișare populație
    print('Cromozomi generați automat:')
    for c in popu.cr:
        x1 = c.getv(1)
        vfx1 = fx1(x1)
        print('%2d: %s, coeficient de adecvare %f, f(%.3f)=%f' %
                (c.id, c.sir(), adecv(c), x1, vfx1) )
        pylab.plot(x1, vfx1, 'go', linewidth=2, markersize=6)


    for gnr in range(60):
        print('')
        print('gen #%2d: încrucișări ..' % gnr)
        popu.xbin(adecv)

        print('gen #%2d: mutații ..' % gnr)
        popu.mbin(adecv)

        fg = []                 # fitnes generația curentă
        fgmax = 0               # fitnes maxim al generației curente
        icmax = 0               # index cromozom cu fitnes maxim
        for i, c in enumerate(popu.cr):
            a = adecv(c)
            fg.append(a)
            if a > fgmax:
                fgmax = a       # adjustare maxim
                icmax = i
            x1 = c.getv(1)      # afișare punct
            vfx1 = fx1(x1)
            pylab.plot(x1, vfx1, 'b+')

        x1 = popu.cr[icmax].getv(1)
        vfx1 = fx1(x1)
        print('gen #%2d: fitnes total %f' % (gnr, sum(fg)))
        print('         fitnes maxim %f (cr#%d)' % (fgmax, icmax))
        print('         %s, f(%f)=%f' % (popu.cr[icmax].sir(), x1, vfx1 ))
        if abs(vfx1 - fx1min) < err:
            print('eroarea de aproximare < err')
            pylab.plot(x1, vfx1, 'rd')
            break
        else:
            pylab.plot(x1, vfx1, 'r.')

    # afișare grafic
    pylab.axis([a1,b1, -1.3,0.3])
    pylab.show()


if __name__ == '__main__':
    main()
