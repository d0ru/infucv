/**
 * Algoritmi genetici — cromozom, codificare liste de adiacență.
 * - fiecare genă este codificată printr-un întreg (32 biți)
 *
 * Problema comis-voiajorului
 * --------------------------
 * Soluția problemei este un cromozom de dimensiune „n” construit
 * după regula: orajul „j” este situat pe poziția „i” dacă există
 * o muchie sau drum i↦j.
 *
 * Traseu: 1 ↦ 2 ↦ 4 ↦ 3 ↦ 8 ↦ 5 ↦ 9 ↦ 6 ↦ 7
 * ListăA: (2, 4, 8, 3, 9, 7, 1, 5, 6)
 */

//#define NDEBUG

#include "libcrmzla.h"
#include <stdlib.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int n;

	cout << "Introduceți număr orașe: ";
	cin >> n;
	if (n < 0) {
		cerr << argv[0]
		     << ": numărul introdus este invalid "
		     << "(" << n << ")"
		     << endl;
		return 1;
	}

	crmzla cz(n);		// un cromozom
	cz.readg("Introduceți traseul: ");

	// codificare
	cout << endl
	     << "Am codificat următorul traseu: "
	     << cz
	     << endl;

	// decodificare
	cout << endl
	     << "Am decodificat următorul traseu:";
	cz.decodg();
	return 0;
}
