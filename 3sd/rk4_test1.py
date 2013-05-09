#!/usr/bin/env python
# -*- coding: utf-8 -*-

from rungekutta import rk4pasfix
from math import sqrt

# http://rosettacode.org/wiki/Runge-Kutta_method
def yp(y, t):
    """ derivata parțială de ordinul I """
    return t * sqrt(y)

def y(t):
    """ soluția exactă calculată analitic """
    return ((t**2 + 4) ** 2) / 16.0


def main():
    y0, t0, dt, tmax = 1.0, 0.0, 0.1, 10.0
    (yn, tn) = rk4pasfix(yp, y0, t0, dt, tmax)
    for i in range(0, len(tn), 10):
        print ("y(%2.1f)\t = %4.6f \t error:%4.6g" % (tn[i], yn[i], abs(yn[i] - y(tn[i]))))

if __name__ == '__main__':
    main()
