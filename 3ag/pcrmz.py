# -*- coding: utf-8 -*-
""" Algoritmi genetici — operații cu populații de cromozomi """

from __future__ import print_function
import random


class PCrmz(object):
    """ PCRMZ — populație cromozomi """
    id = 0      # identificator
    cr = []     # vector cromozomi
    def __init__(self, id = None):
        super(PCrmz, self).__init__()
        # numărul de instanțe ale clasei
        PCrmz.id += 1

        if id:
            self.id = id
        else:
            self.id = PCrmz.id

        # fiecare populație trebuie să aibă o secvență unică de cromozomi
        self.cr = []

    def sel(self, fadecv, nc=0, info=False):
        """ Metodă de selecție cromozomi: ruleta
        - fadecv(cr): funcția de adecvare (sau fitnes)
        - nc: numărul de cromozomi selectați (implicit 50% din populație)

        Returnează o listă cu indexul cromozomilor selectați.
        """
        if nc <= 0:
            nc = len(self.cr) // 2  # valoarea implicită

        # calculează fitnes individual și total
        f = [float(fadecv(c)) for c in self.cr]
        ftot = sum(f)

        ptai = []       # tăieturi în intervalul de probabilități: [0.0, 1.0]
        pc = 0          # cumulul curent de probabilități p0+..+pi
        for pi in [fi/ftot for fi in f]:
            pc += pi
            ptai.append(pc)
        if info:
            print('S probabilități cumulate: %s' % ptai)

        crsel = []                  # lista cromozomilor selectați
        while len(crsel) < nc:
            na = random.random()    # [0, 1)
            ic = len([p for p in ptai if p < na])
            if ic not in crsel:
                crsel.append(ic)
                if info:
                    print('- selectat cr#%d (fitnes %f) cu %f < %f' %
                            (ic+1, f[ic], na, ptai[ic]) )
        return crsel

    def x2bin(self, ic1, ic2, nt=0, info=False):
        """ Încrucișarea binară a doi cromozomi
        - ic1: indexul primului cromozom în vectorul cr[]
        - ic2: indexul cromozomului secund
        - nt: numărul de tăieturi (implicit 20% din numărul de gene)

        Metoda operează direct pe cromozomii părinți și îi
        înlocuiește cu descendenții lor.
        """
        if nt <= 0:
            nt = len(self.cr[0].g) // 5     # valoarea implicită

        gtai = []                   # gene selectate pentru tăieturi
        while len(gtai) < nt:
            ri = random.randint(0, (len(self.cr[0].g) - 1))
            if ri not in gtai:
                gtai.append(ri)
        gtai.sort()                 # sortează crescător tăieturile

        # dacă ultima tăietură nu are pereche?
        if nt % 2:
            gtai.append(len(self.cr[0].g) - 1)   # implicit până la sfârșit
        if info:
            print('X2 gene selectate: %s' % gtai)

        # interschimbă genele cromozomilor per tăietură [start, final]
        for s, f in zip(gtai[0::2], gtai[1::2]):
            f += 1                  # adjustare pentru tăietură listă
            tmp = self.cr[ic1].g[s:f]                   # tmp ← cr1
            self.cr[ic1].g[s:f] = self.cr[ic2].g[s:f]   # cr1 ← cr2
            self.cr[ic2].g[s:f] = tmp[:]                # cr2 ← tmp
            del tmp
        if info:
            print('%2d: %s' % (self.cr[ic1].id, self.cr[ic1].sir()))
            print('%2d: %s' % (self.cr[ic2].id, self.cr[ic2].sir()))

    def xbin(self, fadecv, nc=0, nt=0, info=False, selinfo=False):
        """ Încrucișarea binară a unui set aleator de cromozomi
        - fadecv(cr): funcția de adecvare (sau fitnes)
        - fsel(fadecv, nc): funcția de selecție cromozomi
        - nc: numărul de cromozomi selectați (implicit 50% din populație)
        - nt: numărul de tăieturi (implicit 20% din numărul de gene)

        Metoda operează direct pe populație și înlocuiește
        cromozomii părinți cu descendenții lor.
        """
        crsel = self.sel(fadecv, nc, info=selinfo)  # selecție
        if info:
            print('X cromozomi selectați: %s' % crsel)

        # se aleg aleator câte doi cromozomi din cei selectați
        while len(crsel) > 1:
            ri = random.randint(0, len(crsel)-1)
            ic1 = crsel[ri]             # prim
            del crsel[ri]
            ri = random.randint(0, len(crsel)-1)
            ic2 = crsel[ri]             # secund
            del crsel[ri]
            self.x2bin(ic1, ic2, nt, info=info)     # încrucișare

    def m1bin(self, ic, pm = 0.25, info=False):
        """ Mutația binară tare a unui singur cromozom
        - ic: index cromozom în vectorul cr[]
        - pm: probabilitatea de mutație ∈ [0, 1] (implicit 0.25)

        Metoda operează direct pe cromozom și înlocuiește
        genele ce au o probabilitate aleatoare ρ < pm.
        """
        print('M2 gene selectate:', end='')
        for i in range(len(self.cr[ic].g)):
            rho = random.random()       # [0, 1)
            if rho < pm:
                print(' %d' % i, end='')
                if self.cr[ic].g[i]:    # =1
                    self.cr[ic].g[i] = 0
                else:
                    self.cr[ic].g[i] = 1
        print('')
        print('%2d: %s' % (self.cr[ic].id, self.cr[ic].sir()))

    def mbin(self, fadecv, nc = 0, pm = 0.25, info=False, selinfo=False):
        """ Mutația binară tare a unui set aleator de cromozomi
        - fadecv(cr): funcția de adecvare (sau fitnes)
        - fsel(fadecv, nc): funcția de selecție cromozomi
        - nc: numărul de cromozomi selectați (implicit 20% din populație)
        - pm: probabilitatea de mutație ∈ [0, 1] (implicit 0.25)

        Metoda operează direct pe populație și înlocuiește
        genele ce au o probabilitate aleatoare ρ < pm.
        """
        if nc <= 0:
            nc = len(self.cr) // 5  # valoarea implicită

        crsel = self.sel(fadecv, nc, info=selinfo)  # selecție
        if info:
            print('M cromozomi selectați: %s' % crsel)

        for ic in crsel:
            self.m1bin(ic, pm, info=info)           # mutație cromozom
