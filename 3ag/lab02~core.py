#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test codificare și decodificare
a unui cromozom în codificare reală.
"""

import crmz


def main():
    cr = crmz.CrmzCR(4)
    cr.setx((-3, 12.1, '010001001011010000'),
            (4.1, 5.8, '111110010100010'))
    print('cr#%d: %d variabile, precizie %d cifre zecimale' % (cr.id, len(cr.ln), cr._p))
    f = 0
    for i, l in enumerate(cr.ln):
        # variabila curentă este reprezentată în cromozom astfel:
        #   .. s+[0..l-1] ..
        s = f        # prima genă
        f = s + l    # ultima genă (+1)
        print('  x%d: %s (%d biți)' % ((i+1), cr.sir(s,f), l))
        print('    = %f ∈ [%f, %f]' % (cr.getv(i+1), cr.ab[i][0], cr.ab[i][1]))


if __name__ == '__main__':
    main()
