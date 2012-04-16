/**
 * Fie x1, x2,.. xn o secvență de «n» numere întregi distincte.
 * Perechea (i,j) se numește inversiune dacă xi > xj, cu 1 ≤ i < j ≤ n.
 * Exemplu: secvența "2 4 3 1 5 6 9" are 4 inversiuni.
 *
 * Cerință
 * -------
 * Scrieți un program care pentru fiecare secvență de numere citită
 * din fișierul de intrare, scrie în fișierul de ieșire numărul de
 * inversiuni din secvență.
 * Fiecare rezultat va fi scris pe o linie separată.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// citire secvență de numere
int *citire_secventa(FILE *fisier, unsigned short int *dimensiune);

// calculează numărul de inversiuni dintr-o secvență de numere
int nr_inversiuni(unsigned short int dimensiune, int secventa[]);

/**
 * Soluție
 * =======
 * Se citește pe rând câte o secvență de numere întregi din fișierul
 * de intrare «inversiuni.in». Dacă fișierul este gol sau au fost
 * citite toate secvențele de numere, funcția «citire_secventa» va
 * returna NULL.
 * Memoria se alocă dinamic pentru fiecare secvență în parte și este
 * eliberată înainte de citirea următoarei secvențe de numere.
 * Am folosit "int" pentru numere întregi generice în limbajul C.
 *
 * Pentru calculul numărului de inversiuni am folosit algoritmul
 * “merge sort” de complexitate θ(n•lg(n)).
 * Numărul maxim de inversiuni se obține când toate numerele sunt
 * sortate în ordine strict descrescătoare.
 *
 * Limitare
 * ========
 * Programul nu tratează situația în care la intrare sunt date (eronat)
 * mai multe sau mai puține numere decât a fost declarat prin numărul
 * ce precede secvența de numere.
 * Date din fișierul de intrare se consideră a fi corecte.
 */
int main(void)
{
	FILE *fintrare;				// "r" din «inversiuni.in»
	FILE *fiesire;				// "w" în «inversiuni.out»
	int *secventa;				// vector alocat dinamic
	unsigned short int dimensiune;		// dimensiune secvență
	int nrinv;				// inversiuni în secvență

	fintrare = fopen("inversiuni.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «inversiuni.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("inversiuni.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «inversiuni.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	// dacă fișierul de intrare este gol, bucla nu se execută
	while (NULL != (secventa = citire_secventa(fintrare, &dimensiune))) {
		nrinv = nr_inversiuni(dimensiune, secventa);
		fprintf(fiesire, "%d\n", nrinv);
		free(secventa);			// eliberează memoria alocată
	}
	return 0;
}

// COMPLEXITATE timp θ(n) | spațiu θ(n)
int *citire_secventa(FILE *fisier, unsigned short int *dimensiune)
{
	int *secventa, *numar;
	short int i;				// maxim 10,000

	// citesc dimensiunea secvenței de numere întregi
	if (1 != fscanf(fisier, "%hu", dimensiune))
		return NULL;			// eroare de citire sau
						// sfârșit de fișier

	secventa = (int *) malloc(sizeof(int) * (*dimensiune));
	if (NULL == secventa) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru o secvență de «%d» numere întregi\n", *dimensiune);
		return NULL;
	}

	// nu se verifică corectitudinea sau numărul datelor de intrare
	for (i = 0, numar = secventa; i < *dimensiune; i++, numar++)
		fscanf(fisier, "%d", numar);
	return secventa;
}

// COMPLEXITATE timp θ(n•lg(n)) | spațiu θ(n)
int nr_inversiuni(unsigned short int dimensiune, int secventa[])
{
	int cheia;
	int i, j;				// maxim 10,000
	int nrinv;				// maxim 50,000,000

	nrinv = 0;
	for (j = 1; j < dimensiune; j++) {
		cheia = secventa[j];
		for (i = j-1; (i >= 0) && (secventa[i] > cheia); --i, ++nrinv)
			secventa[i+1] = secventa[i];
		secventa[i+1] = cheia;
	}
	return nrinv;
}
