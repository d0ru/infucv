/* Să se realizeze o clasă care reprezintă noțiunea de poligon.
 * Poligonul este dat printr-o mulțime de puncte, punctele fiind specificate
 * în ordine trigonometrică.
 * Să se scrie o funcție care calculează perimetrul.
 */

#include <iostream>
using namespace std;

#include <math.h>

#include "lab04_punct.h"
#include "lab04_punct.cpp"
#include "lab04_poligon.h"


void poligon::citire(void)
{
	int i;

	cout << "Introduceți numărul de puncte pentru construcția poligonului: ";
	cin >> this->np;

	if (this->np < 0)
		this->np = 0;
	if (this->np > 10)
		this->np = 10;
	for (i = 0; i < this->np; i++)
		this->p[i].citire();
}

void poligon::afisare(void)
{
	int i;

	cout << "Punctele poligonului sunt: " << endl;
	for (i = 0; i < this->np; i++) {
		cout << "Punctul «" << i << "»: ";
		this->p[i].afisare();
	}
}

float poligon::perimetru(void)
{
	int i;
	float pmetru;

	pmetru = distanta(&this->p[this->np - 1], &this->p[0]);
	for (i = 1; i < this->np; i++) {
		pmetru += distanta(&this->p[i-1], &this->p[i]);

	}
	return pmetru;
}


int main(void)
{
	punct p0, p1(7,6), p2(12), p3=20;
	poligon P;

	p0.afisare();
	p1.afisare();
	p2.afisare();
	p3.afisare();

	P.citire();
	P.afisare();
	cout << P.perimetru();
	return 0;
}
