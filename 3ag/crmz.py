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

    def sirint(self, unu = False, sep = ' '):
        """
        Formează un șir cu toate genele în forma codificată,
        separate printr-un șir dat.
        """
        if not self.g:
            return ''

        if unu:
            start = 1       # reprezentare internă de la 0, externă de la 1
        else:
            start = 0       # nici o diferență de reprezentare
        gstr = [str(self.g[0]+start)]
        gstr += [sep + str(i+start) for i in self.g[1:]]
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
    * fiecare genă este codificată binar (0 sau 1)
    * f(x1,x2,..xn), xi ∈ [ai,bi] ⊂ R cu i=1,n
    * _p: precizia variabilelor, nr. de zecimale exacte
    """
    _p = 0      # precizia de zecimale exacte
    ab = []     # (ai,bi) pentru fiecare variabilă „i”
    ln = []     # lungimea fiecărei variabile
    def __init__(self, pr = 0, id = 0):
        super(CrmzCR, self).__init__(id)
        # precizia nu poate fi negativă
        if pr > 0:
            self._p = pr
        # fiecare obiect trebuie să aibă o secvență unică
        self.ab = []
        self.ln = []

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

    def reset(self, *x):
        """
        Inițializare neinteractivă cromozom.
        Toți parametrii  sunt tupluri de forma (ai, bi, si), unde
        * [ai, bi] este intervalul de valori ale variabilei xi
        * iar 'si' este un șir ce reprezinta codificarea binară (01)
        """
        if self.ab:
            del self.ab
            self.ab = []
        if self.ln:
            del self.ln
            self.ln = []
        if self.g:
            del self.g
            self.g = []

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
        return ai + zi * float(bi - ai) / (2**li - 1)


class CrmzCA(Crmz):
    """
    CrmzCA — cromozom în codificare prin adiacență
    * fiecare genă este codificată printr-un număr întreg
    * gena „i” conține numărul „j” dacă există o muchie sau conexiune [i,j]
    Legături:   1→2→4→3→8→5→9→6→7
    Codificare: 2 4 8 3 9 7 1 5 6
    """
    def __init__(self, nr_gene = 0, id = None):
        super(CrmzCA, self).__init__(id)
        if nr_gene > 0:
            self.g = random.sample(range(nr_gene), nr_gene)

    def traseu(self):
        """
        Decodifică traseul sub forma de conexiuni secvențiale.
        """
        if not self.g:
            return ''

        gstr = ['1']        # primul element
        u = 0
        v = self.g[0]       # prima conexiune
        while v != 0:
            gstr += [' → ' + str(v+1)]
            u = v           # continuare
            v = self.g[u]
        sir = ''.join(gstr)
        del gstr
        return sir

    def reset(self, *x):
        """ Inițializare neinteractivă cromozom.
        Se acceptă un număr variabil de parametrii — traseu sau conexiuni.
        Toate elementele sunt din intervalul [1..n], unde n = dimensiune.
        """
        if self.g:
            del self.g
            self.g = []

        self.g = [0 for i in range(len(x))]     # inițializare
        u = x[0]                                # primul element
        for v in x[1:]:
            self.g[u-1] = v-1   # conexiune [u,v]
            u = v               # continuare


class CrmzCO(Crmz):
    """
    CrmzCO — cromozom în codificare ordinală
    * fiecare genă este codificată printr-un număr întreg
    * gena „i” conține un număr „j”, cu j ∈ [1, n-i+1]
      - „n” reprezintă cardinalul elementelor
      - prima condiție de validare este ca fiecare genă să fie unică, adică
        nu există două apariții ale aceluiași element în cromozom
      - toate elementele au valori cuprinse între 1 și „n”
      - „j” este cardinalul elementului conectat din punctul „i”
    Legături:   1→2→4→3→8→5→9→6→7
    Codificare: 1 1 2 1 4 1 3 1 1
    """
    def __init__(self, nr_gene = 0, id = None):
        super(CrmzCO, self).__init__(id)
        if nr_gene > 0:
            self.g = [random.randint(0, nr_gene - i) for i in range(1, nr_gene+1)]

    def traseu(self):
        """
        Decodifică traseul sub forma de conexiuni secvențiale.
        """
        if not self.g:
            return ''

        gord = range(1, len(self.g)+1)  # „g” ordonat
        gstr = [str(gord[self.g[0]])]   # primul element
        del gord[self.g[0]]
        try:
            for i in self.g[1:]:
                gstr += [' → ' + str(gord[i])]
                del gord[i]
        except IndexError:
            print('E: traseu invalid: gord[%d] nu există!!' % i)

        sir = ''.join(gstr)
        del gstr
        return sir

    def reset(self, *x):
        """ Inițializare neinteractivă cromozom.
        Se acceptă un număr variabil de parametrii — traseu sau conexiuni.
        Toate elementele sunt din intervalul [1..n], unde n = dimensiune.
        """
        if self.g:
            del self.g
            self.g = []

        gord = range(1, len(x)+1)   # „g” ordonat
        for i in x:
            k = gord.index(i)   # al câtelea element este „i”?
            del gord[k]
            self.g.append(k)    # adaug index la codificare

