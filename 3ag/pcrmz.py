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
