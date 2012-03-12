/*
 * Poligonul este dat printr-o mulțime de puncte, punctele fiind specificate
 * în ordine trigonometrică.
 */

#include "lab04_punct.h"

#ifndef __POLIGON__
#define __POLIGON__
// poligon: un set de puncte date în ordine crescatoare
// [p0,p1], [p1,p2].. [pn,p0] sunt muchiile poligonului
class poligon
{
private:
	int np;				// numărul de puncte
	punct p[10];

public:
	void citire(void);
	void afisare(void);
	float perimetru(void);
};
#endif
