/*
 * Să se realizeze o clasă care reprezintă noțiunea de poligon.
 * Poligonul este dat printr-o mulțime de puncte.
 * Se presupune că punctele sunt specificate în ordine trigonometrică.
 */

#include <iostream>
using namespace std;

#include <math.h>

#include "lab04_punct.h"
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

	if (this->np < 1) {
		cout << "Poligonul nu are nici un punct." << endl;
		return;
	}
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
