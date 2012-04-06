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

#include <errno.h>
#include <stdio.h>

/**
 * Soluție
 * -------
 * Se procesează pe rând fiecare nivel (b=bonus, p=putere monstru) și
 * compar unitățile de viață curente cu puterea monstrului. Dacă am
 * mai multă energie decât monstrul folosesc sabia, altfel abracadabra.
 *
 * Sunt tratate cazurile excepționale:
 * - am depășit nivelul maxim de energie (100)
 * - monstrul are puterea maximă (100), deci nu pot să-l înving
 *
 * Observație: pentru depanare se comentează declarea macroului NDEBUG
 */
int main(void)
{
	FILE *fintrare;				// "r" din «joc.in»
	FILE *fiesire;				// "w" în «joc.out»
	short unsigned int i, n, magie;		// limita superioară 20000
	short unsigned int b, p, viata;		// limita superioară 100

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
		return errno;			// eroare de citire sau
						// sfârșit de fișier

	magie = 0;				// de câte ori am folosit magia
	viata = 100;				// unități de viață la start
	i = 0;
	while (i < n) {
		// date de intrare incorecte ↦ comportament imprevizibil
		fscanf(fintrare, "%hu %hu", &b, &p);
		viata += b;			// adaug bonusul de nivel
		if (viata > 100) {
			if (100 == p) {
				viata = 100;
				++magie;		// cuvântul magic
			} else {
				// viața crește doar până la 100 de unități
				viata = 100 - p;	// nimicește monstrul cu sabia
			}
#ifndef NDEBUG
//			fprintf(stdout, "I: energie maximă (nivelul #%hu, b=%hu, p=%hu, viata=%hu)\n", i, b, p, viata);
#endif
		} else if (viata > p) {
			viata -= p;		// nimicește monstrul cu sabia
#ifndef NDEBUG
//			fprintf(stdout, "W: pierd energie (nivelul #%hu, b=%hu, p=%hu, viata=%hu)\n", i, b, p, viata);
#endif
		} else {
			++magie;		// cuvântul magic
#ifndef NDEBUG
			fprintf(stdout, "HOCUS POCUS #%hu (nivelul #%hu, b=%hu, p=%hu, viata=%hu)\n\n", magie, i, b, p, viata);
#endif
		}
		++i;
	}
	fprintf(fiesire, "%hu\n", magie);
	return 0;
}
