/**
 * Se consideră «m» strunguri identice destinate prelucrării automate
 * a unor piese. Strungurile funcționează independent unul de altul.
 *
 * Pentru fiecare piesă «i» se cunoaște timpul d[i] necesar pentru
 * prelucrarea ei pe unul din cele «m» strunguri.
 *
 * Cerință
 * -------
 * Elaborați un program care calculează timpul necesar pentru a
 * prelucra toate piesele.
 *
 * Restricții și precizări
 * -----------------------
 *   2 ≤ m ≤ 100
 *   1 ≤ n ≤ 1000
 *   1 ≤ d[i] ≤ 30, i=1…n
 */

//#define NDEBUG

#include <errno.h>
#include <stdio.h>

#define MAXPIESE	1000

short int d[MAXPIESE];			// 1 ≤ d[i] ≤ 30000 < 2¹⁵
short int m;				// numărul de strunguri
short int n;				// numărul de piese

// citesc dimensiuni și pozițiile tuturor pieselor de pe tablă
int citire_piese(FILE *fisier);

#ifndef NDEBUG
// afisare lungimi pentru cele «m» strunguri
void afisare_strunguri(int start);
#endif

// ordonarea elementelor d[prim,ultim] folosind sortarea “merge”
void msort(int prim, int ultim);

/**
 * Soluție
 * -------
 * Inițial primele «m» piese sunt repartizate câte una pe strunguri.
 * Înlocuim timpul necesar pentru prelucrarea unei piese cu lungimea
 * piesei — cerința se transformă în calculul lungimii maxime.
 *
 * Privim problema din alt unghi de vedere: în loc să scădem din toate
 * piesele câte o unitate până cel puțin una ajunge la 0, vom aduna
 * d[i] la strungul care în acel moment are cea mai mică lungime.
 *
 * Construim un vector care reține lungimea pieselor pe fiecare strung.
 * La fiecare pas vectorul strungurilor este sortat crescător. Așadar,
 * primul strung are cea mai mică lungime → se adaugă piesa următoare.
 * Se ordonează primul strung în vector (a crescut lungimea pieselor)
 * folosind o variantă liniară a algoritmul de sortare “merge” peste
 * un vector parțial ordonat (mai puțin primul element) — θ(lg(m)).
 *
 * Procesul se termină când au fost repartizate toate piesele pe câte
 * un strung. Timpul minim necesar pentru prelucrarea tuturor pieselor
 * este în relație 1:1 cu strungul de lungime maximă ce se determină
 * simplu — complexitate θ(1) — ultima poziție din vectorul sortat.
 *
 * ------
 * Pentru o utilizare cât mai eficientă a memoriei, vom lucra cu un
 * singur vector pentru stocarea lungimii celor «n» piese cât și
 * pentru cele «m» strunguri. Astfel, inițial avem vectorul:
 *   1 2 … m m+1 m+2 … … … n
 *   X X...X  X   X  . . . X (subșirul de «m» elemente este sortat)
 *   ↑     ↑ urm
 *   prim  ultim
 * La prima iterație strung[1] este adăugat la piesa[m+1], prim și
 * ultim sunt incrementate, ultima valoare este sortată în subșir.
 *   - 2 … m m+1 m+2 … … … n
 *   - X...X  X   X  . . . X (subșirul de «m» elemente este sortat)
 *     ↑      ↑  urm
 *     prim   ultim
 * Rezultatul căutat este lungimea maximă de pe poziția «n».
 */
int main(void)
{
	FILE *fintrare;				// "r" din «strung.in»
	FILE *fiesire;				// "w" în «strung.out»
	short int cheia;
	int i, prim, ultim, urm;
#ifndef NDEBUG
	int j;
#endif

	fintrare = fopen("strung.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «strung.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("strung.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «strung.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	i = citire_piese(fintrare);
	if (0 != i)
		return i;			// errno

	// dacă am mai multe strunguri decât piese? (n < m)
	ultim = (m <= n) ? m : n;		// minimul dintre «m» și «n»
	// sortarea inițială a subșirului de min(m,n) elemente
	msort(0, --ultim);
#ifndef NDEBUG
	putchar('[');
	for (j = 0; j < n; ++j)
		printf(" %hd", d[j]);
	puts(" ]\n");
#endif

	// COMPLEXITATE θ(n•lg(m))
	for (prim = 0, urm = m; urm < n;) {	// dacă n ≤ m nu se execută
		// procesez rapid tot ce depășește maximul curent
		do d[urm] += d[prim++];		// adaug lungimea piesei curente
		while ((d[ultim++] <= d[urm++]) && (urm < n));

		// îmbin ultimul element în subșirul presortat
		cheia = d[ultim];
		for (i = ultim-1; d[i] > cheia; --i)
			d[i+1] = d[i];		// mutare la dreapta o poziție
		d[i+1] = cheia;			// poziția ordonată
#ifndef NDEBUG
		afisare_strunguri(prim);
#endif
	}
	fprintf(fiesire, "%hd", d[ultim]);
	return 0;
}

// COMPLEXITATE timp θ(n) | spațiu θ(n)
int citire_piese(FILE *fisier)
{
	int i;

	// citesc numărul de strunguri și piese
	if (2 != fscanf(fisier, "%hd %hd", &m, &n))
		return errno;			// eroare de citire
#ifndef NDEBUG
	printf("m=%hd, n=%hd\n", m, n);
#endif
	for (i = 0; i < n; ++i)
		fscanf(fisier, "%hd", d+i);
	return 0;
}

#ifndef NDEBUG
// COMPLEXITATE θ(m)
void afisare_strunguri(int start)
{
	int i;

	printf("[%3i,%3i]:", start, start+m-1);
	for (i = 0; i < m; ++i)
		printf(" %hd", d[start+i]);
	if ((start+m) < n)
		printf(" ↦ %hd", d[start+m]);
	putchar('\n');
}
#endif

// COMPLEXITATE θ(n•lg(n))
void msort(int prim, int ultim)
{
	int i, j;
	short int cheia;

	for (j = prim+1; j <= ultim; ++j) {
		cheia = d[j];
		for (i = j-1; (i >= prim) && (d[i] > cheia); --i)
			d[i+1] = d[i];
		d[i+1] = cheia;
	}
}
