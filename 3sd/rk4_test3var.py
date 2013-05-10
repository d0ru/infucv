#!/usr/bin/env python
# -*- coding: utf-8 -*-

from rungekutta import rk4pasvar
import numpy

# http://en.wikipedia.org/wiki/Lorenz_attractor
def yp(yv, t, sigma = 10., rho = 28., beta = 8./3.):
    """ derivata parțială de ordinul I """
    [x, y, z] = yv.tolist()
    dx = sigma * (y - x)
    dy = x * (rho - z) - y
    dz = x * y - beta * z
    return numpy.asarray([dx, dy, dz])


def main():
    y0, t0, dt0, tmax = numpy.asarray([1, 2, -1]), 0.0, 0.05, 2.0
    (yn, tn, en) = rk4pasvar(yp, y0, t0, dt0, tmax)
    print ("  t       | Soluția numerică a punctelor  [x y z] %6s | Eroare (Δt = %g)" % (' ', dt0))
    print ('-' * 77)
    for i in range(0, len(tn)):
        print (" %2.6f |   %-42s | %5.15f" % (tn[i], yn[i], en[i]))
    print('')

if __name__ == '__main__':
    main()
