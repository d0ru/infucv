/**
 * Se consideră un joc electronic în care trebuie să parcurgi un drum
 * lung, de-a lungul căruia se află «n» monștri.
 *
 * În orice moment din joc ai o viață 1 ≤ V ≤ 100 (inițial 100).
 * Trebuie să distrugi câte un monstru (în ordinea dată 1, 2,.. n) cu
 * sabia sau un cuvînt magic. Dacă nimicești monstrul «i» cu ajutorul
 * sabiei, pierzi din viata ta p[i] unități. Dacă însă distrugi monstrul
 * pronunțând cuvântul magic, nu pierzi nimic din viața ta.
 *
 * Cerință
 * -------
 * Scrie un program care te ajută să câștigi jocul astfel încât cuvântul
 * magic să fie pronunțat de un număr minimal de ori.
 *
 * Restricții și precizări
 * -----------------------
 *   1 ≤ n ≤ 20000; 1 ≤ b[i],p[i] ≤ 100
 *   1 ≤ n < 100 pentru 20% din teste
 *   100 ≤ n < 10000 pentru 60% din teste
 *   10000 ≤ n ≤ 20000 pentru 20% din teste
 */

//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPUTERE	100

short unsigned int n;				// limita superioară 20000
unsigned char *bonus;
unsigned char *monstru;
unsigned char *energie;

// citesc informații de nivel (b+p) și calculez «pmin»
void citire_nivele(FILE *fisier);

// luptă cu fiecare monstru în ordine cronologică
int lupta_monstri(void);

/**
 * Soluție
 * -------
 * Se procesează pe rând fiecare nivel (b=bonus, p=putere monstru) și
 * compar unitățile de viață curente cu puterea monstrului. Dacă am
 * mai multă energie decât monstrul folosesc sabia, altfel abracadabra.
 *
 * divide et impera: toate nivelurile sunt împărțite în mai multe serii
 * independente, o serie avand unul sau mai multe nivele. Orice serie se
 * încheie cu un nivel la care nu am suficientă energie pentru a învinge
 * monstrul cu sabia. Așadar în fiecare serie am voie să aplic magia
 * *doar* o singură dată.
 *
 * Cunoscând primul și ultimul nivel dintr-o serie se calculează cea
 * mai bună strategie de luptă pentru ca aplicând magia o singură dată
 * să rămân cu cât mai multă viață la încheierea seriei.
 *
 * Sunt tratate cazurile excepționale:
 * - am depășit nivelul maxim de unități convenționale (100)
 * - monstrul are puterea maximă (100), nu pot să-l înving cu sabia
 *
 * Observație: pentru depanare se comentează declarea macroului NDEBUG
 */
int main(void)
{
	FILE *fintrare;				// "r" din «joc.in»
	FILE *fiesire;				// "w" în «joc.out»
	int nrmagie;

	fintrare = fopen("joc.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «joc.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("joc.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «joc.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	// citesc numărul de monștri
	if (1 != fscanf(fintrare, "%hu", &n))
		return errno;			// eroare de citire

	bonus = (unsigned char *) malloc(sizeof(unsigned char) * n);
	if (NULL == bonus) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul bonus[%hu]\n", n);
		return errno;
	}

	monstru = (unsigned char *) malloc(sizeof(unsigned char) * n);
	if (NULL == monstru) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul monstru[%hu]\n", n);
		return errno;
	}

	energie = (unsigned char *) malloc(sizeof(unsigned char) * n);
	if (NULL == energie) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul energie[%hu]\n", n);
		return errno;
	}

	citire_nivele(fintrare);
	nrmagie = lupta_monstri();
	fprintf(fiesire, "%i\n", nrmagie);
	return 0;
}

// COMPLEXITATE timp Θ(n) | spațiu Θ(n)
void citire_nivele(FILE *fisier)
{
	int i;
	short unsigned int b, p;		// limita superioară MAXPUTERE
	unsigned char *pb;			// element curent bonus[]
	unsigned char *pm;			// element curent monstru[]

	pb = bonus; pm = monstru;
	for (i = 0; i < n; ++i, ++pb, ++pm) {
		// date de intrare incorecte ↦ comportament impredictibil
		fscanf(fisier, "%hu %hu", &b, &p);
		*pb = (unsigned char) b;	// conversie la 1 octet
		*pm = (unsigned char) p;

		// depanare: verific datele de intrare
		assert(*pb <= MAXPUTERE);
		assert(*pm <= MAXPUTERE);
#ifndef NDEBUG
//		fprintf(stdout, "I: nivelul #%i, b=%u, p=%u\n", i, *pb, *pm);
#endif
	}
}

// COMPLEXITATE O(d²)
int o_magie(unsigned char *viata, int prim, int ultim)
{
	int i, j, nmax;
	unsigned char vmax;

	nmax = ultim;				// implicit: ultimul nivel
	for (i = ultim-1; i >= prim; --i) {
		vmax = energie[i] + bonus[i];	// aplică magia pe monstrul «i»
		if (vmax > 100)
			vmax = 100;		// energia maximă posibilă

		// recalculez energia rămasă până la nivelul «ultim»
		for (j = i+1; j <= ultim; ++j) {
			vmax += bonus[j];
			if (vmax > 100)
				vmax = 100;
			if (vmax > monstru[j]) {
				vmax -= monstru[j];	// lupt cu sabia
			} else {
				vmax = 0;	// nu pot aplica iar magia
				break;
			}
		}

		// salvez cea mai bună strategie de luptă
		if (*viata < vmax) {
			*viata = vmax;
			nmax = i;
#ifndef NDEBUG
			if (monstru[i] < monstru[ultim])
				fprintf(stdout, "D: @%i BUTURUGA MICĂ #%i RĂSTOARNĂ CARUL MARE %u < %u (vmax = %u)\n", ultim, i, monstru[i], monstru[ultim], vmax);
#endif
		}
	}
	return nmax;
}

// COMPLEXITATE O(n+∑d²)
int lupta_monstri(void)
{
	int nmax, prim, ultim;			// delimitatori serie niveluri
	int nrmagie;				// de câte ori am folosit magia
	unsigned char viata;			// limită superioară MAXPUTERE
	unsigned char *pb;			// element curent bonus[]
	unsigned char *pm;			// element curent monstru[]

	viata = 100;				// unități de viață la start
	pb = bonus; pm = monstru;
	for (prim = ultim = 0, nrmagie = 0; ultim < n; ++ultim, ++pb, ++pm) {
		energie[ultim] = viata;		// energia la începutul nivelului curent
		viata = (unsigned char)(viata + *pb);
		if (viata >= 100) {
			viata = 100;
			prim = ultim;		// încep o nouă serie de aici
#ifndef NDEBUG
			fprintf(stdout, "I: energie maximă (nivelul #%i, e=%u, b=%u, p=%u, viata=%u)\n", ultim, energie[ultim], *pb, *pm, viata);
#endif
		}

		if (100 == *pm) {
			++nrmagie;		// doar magia ne poate ajuta
			prim = ultim + 1;	// încep seria de la următorul nivel
#ifndef NDEBUG
			fprintf(stdout, "ABRACADABRA #%hu (nivelul #%i, e=%u, b=%u ⌊%u⌉, viata=%u)\n", nrmagie, ultim, energie[ultim], *pb, *pm, viata);
#endif
			continue;
		}

		if (viata > *pm) {
			// nimicește monstrul cu sabia
			viata = (unsigned char)(viata - *pm);
#ifndef NDEBUG
			fprintf(stdout, "D: pierd energie (nivelul #%i, e=%u, b=%u, p=%u, viata=%u)\n", ultim, energie[ultim], *pb, *pm, viata);
#endif
		} else {
			// doar magia ne poate ajuta
			if ((viata < 100 - *pm) && (prim < ultim)) {
#ifndef NDEBUG
				fprintf(stdout, "W: monstru prea puternic (nivelul #%i, e=%u, b=%u ⌊%u⌉ viata=%u)\n", ultim, energie[ultim], *pb, *pm, viata);
				fprintf(stdout, "I: caut uriasul din seria [%i..%i]\n", prim, ultim);
#endif
				// folosesc o singură dată magia cât mai eficient
				nmax = o_magie(&viata, prim, ultim);
#ifndef NDEBUG
			} else {
				fprintf(stdout, "I: *NU* caut altă strategie mai eficientă (%u ≥ 100 - %u)\n", viata, *pm);
				nmax = ultim;
#endif
			}

			++nrmagie;
			prim = ultim + 1;	// încep seria de la următorul nivel
#ifndef NDEBUG
			fprintf(stdout, "HOCUS POCUS #%i (nivelul #%i, e=%u, b=%u ⌊%u⌉ viat@=%u)\n\n", nrmagie, nmax, energie[nmax], bonus[nmax], monstru[nmax], viata);
#endif
		}
	}
	return nrmagie;
}
