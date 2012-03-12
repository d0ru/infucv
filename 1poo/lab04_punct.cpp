/* Să se realizeze o clasă care reprezintă noțiunea de poligon.
 * Poligonul este dat printr-o mulțime de puncte, punctele fiind specificate
 * în ordine trigonometrică.
 * Să se scrie o funcție care calculează perimetrul.
 */

#include <iostream>
using namespace std;

#include "lab04_punct.h"


// constructor
punct::punct(float x, float y)
{
	this->x = x;
	this->y = y;
}

float punct::getx(void)
{
	return this->x;
}

float punct::gety(void)
{
	return this->y;
}

void punct::citire(void)
{
	cout << "Introduceți coordonatele punctului: ";
	cin >> this->x >> this->y;
}

void punct::afisare(void)
{
	cout << '(' << this->x << "; " << this->y << ')' << endl;
}

void punct::afisare(char *prefix)
{
	if (NULL != prefix)
		cout << prefix;
	cout << '(' << this->x << "; " << this->y << ')' << endl;
}


// calculează distanța dintre două puncte date
float distanta(punct *p1, punct *p2)
{
	float x1,x2, y1, y2, d;

	x1 = p1->getx();
	y1 = p1->gety();
	x2 = p2->getx();
	y2 = p2->gety();
	d = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	d = sqrt(d);
	return d;
}
