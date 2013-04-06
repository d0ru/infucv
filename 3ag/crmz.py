# -*- coding: utf-8 -*-
""" Algoritmi genetici — operații pe cromozomi """

import math
import random


class Crmz(object):
    """ CRMZ — cromozom generic """
    id = 0      # identificator
    g  = []     # gene
    def __init__(self, id = None):
        super(Crmz, self).__init__()
        # numărul de instanțe ale clasei
        Crmz.id += 1

        if id:
            self.id = id
        else:
            self.id = Crmz.id

        # fiecare obiect trebuie să aibă o secvență unică
        self.g = []

    def sir(self, start = 0, final = None):
        """
        Formează un șir cu genele din intervalul dat.
        Dacă nu este dat un interval, sunt afișate toate genele.
        """
        if not final:
            final = len(self.g)
        gstr = [str(i) for i in self.g[start:final]]
        sir = ''.join(gstr)
        del gstr
        return sir


class CrmzCB(Crmz):
    """ CRMZCB — cromozom în codificare binară
    * fiecare genă este codificată binar (0 sau 1)
    """
    def __init__(self, nr_gene = 0, id = None):
        super(CrmzCB, self).__init__(id)
        self.g = [random.randint(0,1) for i in range(nr_gene)]


class CrmzCR(Crmz):
    """ CRMZCR — cromozom în codificare reală
    * fiecare cromozom are asociat una sau mai multe variabile
    * f(x1,x2,..xn), xi ∈ [ai,bi] ⊂ R cu i=1,n
    * _p: precizia variabilelor, nr. de zecimale exacte
    * fiecare variabilă este codificată binar (0 sau 1)
    """
    _p = 0      # precizia de zecimale exacte
    ab = []     # (ai,bi) pentru fiecare variabilă „i”
    ln = []     # lungimea fiecărei variabile
    def __init__(self, pr = 0, id = 0):
        super(CrmzCR, self).__init__(id)
        # precizia nu poate fi negativă
        if pr > 0:
            self._p = pr

    def _advar(self, ai, bi, si = ''):
        """ Adaugă o variabilă în cromozom """
        if ai > bi:
            ai, bi = ai, bi     # interval: ai < bi
        self.ab.append( (ai,bi) )

        li = int(math.log((bi - ai) * 10**self._p, 2) + 1)
        self.ln.append(li)

        # inițializează gene
        if si:
            self.g += list(si)
        else:
            self.g += [random.randint(0,1) for i in range(li)]

    def setx(self, *x):
        """
        Inițializare neinteractivă cromozom.
        Toate variabilelor sunt tupluri de forma (ai, bi, si), unde
        * [ai, bi] este intervalul de valori ale variabilei xi
        * iar 'si' este un șir ce reprezinta codificarea binară (01)
        """
        if self.ab: del self.ab
        if self.ln: del self.ln
        # fiecare variabilă xi este un tuplu de 3 elemente
        for (ai, bi, si) in x:
            self._advar(ai, bi, si.strip())

    def getv(self, i):
        """ Calculează valoarea lui x[i], cu i=1,n (nu de la 0) """
        assert(1 <= i <= len(self.ln))
        i -= 1
        (ai, bi) = self.ab[i]
        li = self.ln[i]         # număr gene asociate variabilei xi
        si = sum(self.ln[:i])   # prima genă din cromozom pentru xi
        zi = int(self.sir(si, si+li), 2)    # numărul zecimal
        return ai + zi * (bi - ai) / (2**li - 1)
