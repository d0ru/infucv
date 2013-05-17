#!/usr/bin/env python
# -*- coding: utf-8 -*-

from rungekutta import rk4pasvar
import numpy

from matplotlib import pyplot
from mpl_toolkits.mplot3d import axes3d

# http://en.wikipedia.org/wiki/Lorenz_attractor
def yp(yv, t, sigma = 10., rho = 28., beta = 8./3.):
    """ derivata parțială de ordinul I """
    [x, y, z] = yv.tolist()
    dx = sigma * (y - x)
    dy = x * (rho - z) - y
    dz = x * y - beta * z
    return numpy.asarray([dx, dy, dz])


def main():
    # creează figură
    fig = pyplot.figure()
    ax = fig.add_subplot(111, projection='3d')

    # setează etichetele și titlul
    ax.set_xlabel('Axa X')
    ax.set_ylabel('Axa Y')
    ax.set_zlabel('Axa Z')
    ax.set_title('Atractorul Lorenz 3D')

    y0, t0, dt0, tmax = numpy.asarray([-7.5, -3.6, 30.]), 0.0, 0.05, 26.0
    (yn, tn, en) = rk4pasvar(yp, y0, t0, dt0, tmax)
    print ("  t       | Soluția numerică a punctelor  [x y z] %6s | Eroare (Δt = %g)" % (' ', dt0))
    print ('-' * 77)
    x, y, z = [], [], []
    for i in range(0, len(tn)):
        print (" %2.6f |   %-42s | %5.15f" % (tn[i], yn[i], en[i]))
        [xi, yi, zi] = yn[i].tolist()
        x.append(xi), y.append(yi), z.append(zi)

    print('')
    ax.plot(x, y, z)
    pyplot.show()


if __name__ == '__main__':
    main()
