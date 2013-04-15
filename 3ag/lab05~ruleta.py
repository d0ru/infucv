#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test de selectare aleatoare a unei
populații de cromozomi folosind metoda ruletei.
"""

import crmz
import random

def adecv(i):
    rez = [2.1, 1.8, 1.6, 1.4, 1.2, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0]
    try:
        return rez[i-1]
    except IndexError:
        return 0.0
    except:
        print('E: index neașteptat: %s' % str(i))
        raise


def ruleta(popu, fadecv, ns):
    f = [fadecv(cr.id) for cr in popu]
    ftot = sum(f)       # fitnes total

    pr = [fi/ftot for fi in f]
    p = []
    pt = 0
    for pi in pr:
        pt += pi
        p.append(pt)
    print(p)

    for i in range(ns):
        na = random.random()
        nc = len([pi for pi in p if pi < na])
        print('Am selectat cr#%d cu probabilitatea %f < %f' % (nc+1, na, p[nc]))


def main():
    n = 20      # dimensiune cromozom
    m = 14      # dimensiune populație

    popcr = []
    # inițializare populație
    for i in range(m):
        popcr.append(crmz.CrmzCB(n))

    # afișare populație
    print('Ce cromozomi în codificare binară au fost generați automat?');
    for cr in popcr:
        print('%d: %s, coeficient de adecvare %f' % (cr.id, cr.sir(), adecv(cr.id)))

    print('')
    ruleta(popcr, adecv, 6)


if __name__ == '__main__':
    main()
