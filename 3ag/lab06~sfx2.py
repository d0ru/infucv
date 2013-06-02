#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test de selectare aleatoare a unei
populații de cromozomi folosind metoda ruletei.
"""

import crmz
import pcrmz


def fx2(x):
    [x1, x2] = x[:2]
    return x1 + x2

a1, b1 = -3, 7
a2, b2 = -1, 9
funcmin = fx2([a1, a2])
funcmax = fx2([b1, b2])
print('fmin=%f fmax=%f' % (funcmin, funcmax))

def adecv(cr):
    """ Funcția de adecvare asociată funcției fx2 """
    x1 = cr.getv(1)
    x2 = cr.getv(2)
    return (funcmax - fx2([x1, x2]))

def main():
    m = 10      # dimensiune populație
    popu = pcrmz.PCrmz()
    # inițializare populație
    for i in range(m):
        popu.cr.append(crmz.CrmzCR(pr = 4))
        popu.cr[-1].reset( (a1, b1, ''),
                           (a2, b2, '') )

    # afișare populație
    print('Cromozomi generați automat:')
    for c in popu.cr:
        x1 = c.getv(1)
        x2 = c.getv(2)
        print('%2d: %s, fitnes %f, f(%.2f, %.2f)=%f' % (c.id, c.sir(), adecv(c), x1, x2, fx2([x1, x2])))

    print('')
    print popu.sel(adecv, info=True)


if __name__ == '__main__':
    main()
