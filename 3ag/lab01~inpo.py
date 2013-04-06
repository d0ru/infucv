#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test de generare aleatoare a unei
populații de cromozomi în codificare binară.
"""

import crmz


def main():
    try:
        n = int(input('Introduceți dimeniunea cromozomului: '))
        m = int(input('Introduceți dimeniunea populației: '))
    except ValueError:
        print('Sigur ați introdus două numere?')
        raise
    except:
        print('A apărut o excepție neașteptată...')
        raise

    popcr = []
    # inițializare populație
    for i in range(m):
        popcr.append(crmz.CrmzCB(n))

    # afișare populație
    print('')
    print('Ce cromozomi în codificare binară au fost generați automat?');
    for cr in popcr:
        print('%d: %s' % (cr.id, cr.sir()))


if __name__ == '__main__':
    main()
