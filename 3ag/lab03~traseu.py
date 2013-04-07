#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test codificare și decodificare
a unui cromozom reprezentat prin listă adiacențe și
a unui cromozom reprezentat prin listă de ordin.
"""

import crmz


def main():
    cra = crmz.CrmzCA(9)
    #cra.reset(1, 2, 4, 3, 8, 5, 9, 6, 7)
    print('cr#%d: %s (%d)' % (cra.id, cra.sirint(True, ', '), len(cra.g)))
    print('    = %s' % cra.traseu())
    print('')
    cro = crmz.CrmzCO(9)
    #cro.reset(1, 2, 4, 3, 8, 5, 9, 6, 7)
    print('cr#%d: %s (%d)' % (cro.id, cro.sirint(True, ', '), len(cro.g)))
    print('    = %s' % cro.traseu())


if __name__ == '__main__':
    main()
