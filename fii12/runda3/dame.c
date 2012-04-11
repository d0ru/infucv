/**
 * Fie o tablă de șah cu «n» linii și «m» coloane. Pe această tablă
 * sunt plasate mai multe dame și pioni. Considerăm că o damă poate
 * ataca orice poziție (8 direcții), dar cu condiția ca drumul să
 * nu fie blocat de nici o altă piesă.
 *
 * Cerință
 * -------
 * Scrie un program care să calculeze numărul de pătrățele sigure
 * de pe tabla de șah.
 *
 * Restricții și precizări
 * -----------------------
 *   1 ≤ n,m ≤ 1000
 *   0 ≤ nd,np ≤ 100
 *   1 ≤ dx[i],px[j] ≤ n
 *   1 ≤ dy[i],py[j] ≤ m
 */

//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#define MAXTABLA	1000
#define MAXPIESE	100

short int n;				// numărul de linii
short int m;				// numărul de coloane

bool piesa[MAXTABLA+1][MAXTABLA+1];	// se află o piesă pe poziția [x,y]?
bool vizitat[MAXTABLA+1][MAXTABLA+1];	// a fost punctată poziția [x,y]?

short int damax[MAXPIESE+1];		// poziția «x» a damelor pe tabla de șah
short int damay[MAXPIESE+1];		// poziția «y» a damelor pe tabla de șah

// citesc dimensiuni și pozițiile tuturor pieselor de pe tablă
int citire_tabla(FILE *fisier, char *nd, char *np);

#ifndef NDEBUG
// afișare tablă de șah cu piese și poziții controlate
void afisare_tabla(FILE *fisier);
#endif

// calculează numărul punctelor acoperite de dama cu coordonatele [x,y]
int puncte_dama(short int x, short int y);

/**
 * Soluție
 * -------
 * Construim mai multe matrici sau vectori de lucru:
 * - matricea de piese șah conține doar pozițiile damelor și pionilor
 * - matricea de vizite marchează toate pozițiile deja parcurse cât și
 * pozițiile tuturor pieselor de pe tabla de șah
 * - vectorii «damax» și «damay» conțin pozițiile tuturor damelor.
 *
 * Pornim de la numărul maxim de locuri disponibile pe tablă: n × m.
 * Scădem numărul de dame (nd) și numărul de pioni (np). Pentru fiecare
 * damă se calculează numărul de poziții ce sunt incluse în aria de
 * acțiune cu excepția celor care au fost deja marcate anterior.
 */
int main(void)
{
	FILE *fintrare;				// "r" din «dame.in»
	FILE *fiesire;				// "w" în «dame.out»
	char nd;				// numărul de dame
	char np;				// numărul de pioni
	int i, nrps;				// număr pătrățele sigure
						// 0 ≤ nrps ≤ 10⁶ < 2²⁰

	fintrare = fopen("dame.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «dame.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("dame.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «dame.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	i = citire_tabla(fintrare, &nd, &np);
	if (0 != i)
		return i;			// errno

	nrps = (n * m) - nd - np;		// inițializare
	for (i = 1; i <= nd; ++i)
		nrps -= puncte_dama(damax[i], damay[i]);
	// depanare: numărul de pătrățele nu poate fi negativ
	assert(nrps > 0);
	fprintf(fiesire, "%i", nrps);
#ifndef NDEBUG
	afisare_tabla(stdout);
#endif
	return 0;
}

// COMPLEXITATE timp Θ(n⋅m + nd + np) | spațiu Θ(n⋅m + nd)
int citire_tabla(FILE *fisier, char *nd, char *np)
{
	int i, j;
	short int x, y;

	// citesc numărul de linii și coloane
	if (2 != fscanf(fisier, "%hi %hi", &n, &m))
		return errno;			// eroare de citire
#ifndef NDEBUG
	printf("n=%hi, m=%hi\n", n, m);
#endif

	for (i = 0; i <= n; ++i)
		for (j = 0; j <= m; ++j) {
			piesa[i][j] = false;
			vizitat[i][j] = false;
		}

	// citesc numărul de dame
	if (1 != fscanf(fisier, "%i", &i))
		return errno;			// eroare de citire
	*nd = (char) i;
	for (i = 1; i <= *nd; ++i) {
		// citesc și salvez pozițiile damelor pe tabla de șah
		fscanf(fisier, "%hi %hi", &x, &y);
		damax[i] = x;			// linia
		damay[i] = y;			// coloana
		// marchez pozițiile damelor
		piesa[x][y] = true;
		vizitat[x][y] = true;
	}

	// citesc numărul de pioni
	if (1 != fscanf(fisier, "%i", &i))
		return errno;			// eroare de citire
	*np = (char) i;
	for (i = 1; i <= *np; ++i) {
		// citesc pozițiile pionilor pe tabla de șah
		fscanf(fisier, "%hi %hi", &x, &y);
		// marchez pozițiile pionilor
		piesa[x][y] = true;
		vizitat[x][y] = true;
	}
	return 0;
}

#ifndef NDEBUG
// COMPLEXITATE timp Θ(n⋅m + nd + np) | spațiu Θ(n⋅m + nd)
void afisare_tabla(FILE *fisier)
{
	int i, j;

	fprintf(fisier, "%4c", ' ');
	for (j = 1; j <= m; ++j)
		fprintf(fisier, "%3i", j);
	fputc('\n', fisier);

	fprintf(fisier, "%3c", ' ');
	for (j = 0; j <= m; ++j)
		fprintf(fisier, "---");
	fputc('\n', fisier);

	for (i = 1; i <= n; ++i) {
		fprintf(fisier, "%3i|", i);
		for (j = 1; j <= m; ++j)
			if (piesa[i][j])	// avem o piesă
				fprintf(fisier, "  P");
			else if (vizitat[i][j])	// poziție marcată
				fprintf(fisier, "  ×");
			else
				fprintf(fisier, "   ");
		fprintf(fisier, " |\n");
	}

	fprintf(fisier, "%3c", ' ');
	for (j = 0; j <= m; ++j)
		fprintf(fisier, "---");
	fputc('\n', fisier);
}
#endif

// COMPLEXITATE Θ(n+m)
int puncte_dama(short int x, short int y)
{
	int i, j;
	int nrpuncte;

	nrpuncte = 0;
	// direcția 1: pe verticală în jos
	for (i = x-1, j = y; i >= 1; --i) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf("dama[%hi][%hi] → d1:%i", x, y, nrpuncte);
#endif

	// direcția 2: pe verticală în sus
	for (i = x+1, j = y; i <= n; ++i) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d2:%i", nrpuncte);
#endif

	// direcția 3: pe orizontală la stânga
	for (i = x, j = y-1; j >= 1; --j) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d3:%i", nrpuncte);
#endif

	// direcția 4: pe orizontală la dreapta
	for (i = x, j = y+1; j <= m; ++j) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d4:%i", nrpuncte);
#endif

	// direcția 5: pe diagonală la stânga jos
	for (i = x-1, j = y-1; (i >= 1) && (j >= 1); --i, --j) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d5:%i", nrpuncte);
#endif

	// direcția 6: pe diagonală la stânga sus
	for (i = x+1, j = y-1; (i <= n) && (j >= 1); ++i, --j) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d6:%i", nrpuncte);
#endif

	// direcția 7: pe diagonală la dreapta jos
	for (i = x-1, j = y+1; (i >= 1) && (j <= m); --i, ++j) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d7:%i", nrpuncte);
#endif

	// direcția 8: pe diagonală la dreapta sus
	for (i = x+1, j = y+1; (i <= n) && (j <= m); ++i, ++j) {
		if (vizitat[i][j]) {			// poziție marcată
			if (piesa[i][j])
				break;			// avem o piesă
			continue;			// doar un punct vizitat
		}
		vizitat[i][j] = true;			// marchez poziția
		++nrpuncte;
	}
#ifndef NDEBUG
	printf(" d8:%i\n", nrpuncte);
#endif
	return nrpuncte;
}
