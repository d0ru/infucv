/**
 * Algoritmi genetici — cromozom, codificare liste de adiacență.
 * - fiecare genă este codificată printr-un întreg (32 biți)
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libcrmzla.h"

#include <iostream>
using namespace std;

// ctor implicit
crmzla::crmzla(int nrgene, int idgene)
{
	id = idgene;
	if (nrgene <= 0) {		// invalid
		nr = 0;
		g  = NULL;
		return;
	}

	nr = nrgene;			// număr gene
	g = new int[nr+1];		// reprezentare gene
	memset(g, 0, nr+1);		// inițializare ZERO
#ifndef NDEBUG
	cout << "ctor crmzla(" << nr
	     << "," << id
	     << ")" << endl;
#endif
}


// dtor
crmzla::~crmzla()
{
	delete g;
	g = NULL;
#ifndef NDEBUG
	cout << "dtor crmzla(" << nr
	     << "," << id
	     << ")" << endl;
#endif
}


// citire crmzla
void crmzla::readg(const char *mesaj)
{
	int i, s, u, v;		// start, muchia [u,v]
	if (NULL != mesaj)
		cout << mesaj;

	cin >> s;
	for (i = 2, u = s; i <= nr; ++i) {
		cin >> v;
#ifndef NDEBUG
		cout << "[" << u << "," << v << "] " ;
#endif
		if (v <= 0)
			return;
		g[u] = v;
		u = v;		// muchia următoare [u,v]
	}
#ifndef NDEBUG
		cout << "+ [" << u << "," << s << "]" << endl;
#endif
	g[u] = s;		// închidere drum
}


// decodificare gene
void crmzla::decodg(const char *mesaj)
{
	int *pt;		// traseu decodificat
	int *pg;
	int i, u, v;		// muchia [u,v]

	if (nr <= 0)		// invalid
		return;
	if (NULL != mesaj)
		cout << mesaj;

	pt = new int[nr+1];		// reprezentare traseu
	memset(pt, 0, nr+1);		// inițializare ZERO

	for (u = 1, i = 1; i < nr; ++i) {
		v = g[u];
#ifndef NDEBUG
		cout << " [" << u << "," << v << "]";
#endif
		pt[i] = v;
		u = v;		// avansez în listă
	}
#ifndef NDEBUG
	cout << " + [" << u << "," << g[u] << "]" << endl;
#endif
}


// cctor
crmzla::crmzla(const crmzla& cr)
{
	*this = cr;
#ifndef NDEBUG
	cout << "cctor crmzla(" << nr
	     << "," << id
	     << ")" << endl;
#endif
}


// atribuire
crmzla& crmzla::operator=(const crmzla& cr)
{
	if (this == &cr)	// auto atribuire
		return *this;

	delete g;		// eliberează șirul vechi
	if (cr.nr > 0) {
		nr = cr.nr;
		g = new int[nr+1];
		memcpy(g, cr.g, (nr+1) * sizeof(int));	// clonează genele
	} else {		// invalid
		nr = 0;
		g  = NULL;
	}

	id = cr.id;
#ifndef NDEBUG
	cout << "op= crmzla(" << nr
	     << "," << id
	     << ")" << endl;
#endif
	return *this;
}


// supraîncărcare operator
ostream& operator<<(ostream& out, const crmzla& cr)
{
	int *pi = cr.g;		// șir gene
	++pi;			// index de pornire 1, nu 0

	// afișare câte un octet
	out << *pi++;		// prima genă
	for (int i = 2; i <= cr.nr; ++pi, ++i)
		out << " ↦ " << *pi;
	return out;
}
