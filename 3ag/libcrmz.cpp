/**
 * Algoritmi genetici — cromozom.
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libcrmz.h"

#include <iostream>
using namespace std;

// ctor implicit
crmz::crmz(int nrgene, int idgene)
{
	id = idgene;
	if (nrgene <= 0) {		// invalid
		dim = nr = 0;
		g   = NULL;
		return;
	}

	nr = nrgene;			// număr gene
	dim = nrgene;			// număr octeți
	dim /= 8;			// un "char" reține 8 gene
	if (0 != (nrgene % 8))
		++dim;

	g = new unsigned char[dim];		// reprezentare binară gene
#ifndef NDEBUG
	cout << "ctor crmz(" << nr
	     << "," << id
	     << ")" << endl;
#endif
}


// dtor
crmz::~crmz()
{
	delete g;
#ifndef NDEBUG
	cout << "dtor crmz(" << nr
	     << "," << id
	     << ")" << endl;
#endif
}


// inițializare crmz cu gene aleatoare
void crmz::init(void)
{
	unsigned char *c = g;
	for (int i = 0; i < dim; ++i, c++) {
		*c = rand() % 256;
		usleep(60000);
	}
}


// cctor
crmz::crmz(const crmz& cr)
{
	if (this != &cr)
		*this = cr;
#ifndef NDEBUG
	cout << "cctor crmz(" << nr
	     << "," << id
	     << ")" << endl;
#endif
}


// atribuire
crmz& crmz::operator=(const crmz& cr)
{
	if (g != NULL)		// eliberează șirul vechi
		delete g;

	if (cr.dim > 0) {
		dim = cr.dim;
		nr  = cr.nr;
		g = new unsigned char[dim];
		memcpy(g, cr.g, dim);		// clonează genele
	} else {		// invalid
		dim = nr = 0;
		g   = NULL;
	}

	id = cr.id;
#ifndef NDEBUG
	cout << "op= crmz(" << nr
	     << "," << id
	     << ")" << endl;
#endif
	return *this;
}


// afișare octet pe biți
void ucbits(ostream& out, unsigned char c, char b = sizeof(unsigned char) * 8)
{
	size_t poz = sizeof(char) * 8;
	while ((poz-- > 0) && (b-- > 0))
		out << (c >> poz & 1);
}


// supraîncărcare operator
ostream& operator<<(ostream& out, const crmz& cr)
{
	unsigned char *c = cr.g;			// primul octet
	int poz = sizeof(unsigned char) * 8;		// nr. biți per octet

	// afișare câte un octet
	for (int i = cr.nr; i > 0; ++c, i -= poz) {
		if (i <= poz) {
			ucbits(out, *c, i);	// doar primii 'i' biți
			break;			// ultimul octet
		}
		ucbits(out, *c);
#ifndef NDEBUG
		out << ".";
#endif
	}
	return out;
}
