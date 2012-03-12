/*
 * Să se scrie o funcție care calculează perimetrul unui poligon.
 */

#include <iostream>
using namespace std;

#include <math.h>

#include "lab04_punct.h"
#include "lab04_punct.cpp"
#include "lab04_poligon.h"
#include "lab04_poligon.cpp"

int main(void)
{
	poligon P;

	P.citire();
	P.afisare();
	cout << P.perimetru();
	return 0;
}
