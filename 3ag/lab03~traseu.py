#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Acesta este un program test codificare și decodificare
a unui cromozom reprezentat prin listă adiacențe.
"""

import crmz


def main():
    cr = crmz.CrmzCA(9)
    #cr.reset(1, 2, 4, 3, 8, 5, 9, 6, 7)
    print('cr#%d: %s (%d)' % (cr.id, cr.sir(), len(cr.g)))
    print('    = %s' % cr.traseu())


if __name__ == '__main__':
    main()
