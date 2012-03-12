/*
 * Definire și afișare puncte.
 */

#include <iostream>
using namespace std;

#include <math.h>

#include "lab04_punct.h"
#include "lab04_punct.cpp"

int main(void)
{
	punct p0, p1(7,6), p2(12), p3=20;

	p0.afisare();
	p1.afisare();
	p2.afisare();
	p3.afisare();
	return 0;
}
