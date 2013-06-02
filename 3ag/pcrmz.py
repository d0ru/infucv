# -*- coding: utf-8 -*-
""" Algoritmi genetici — operații cu populații de cromozomi """

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
            print('Probabilități cumulate: %s' % ptai)

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
