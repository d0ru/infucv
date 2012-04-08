/**
 * Se consideră cutii n-dimensionale date de cele «n» dimensiuni numere
 * întregi, strict pozitive.
 * Spunem că o cutie x = (x1,x2,..xn) încape în cutia y = (y1,y2,..yn)
 * dacă există o permutare a dimensiunilor cutiei x astfel încât:
 *   x[i] < y[i], ∀i = 1,n
 *
 * Cerință
 * =======
 * Dată o mulțime de cutii n-dimensionale, să se determine cea mai lungă
 * secvență de cutii c1,c2,..ck ce pot fi incluse una în alta. Adică,
 * cutia c[i] încape în cutia c[i+1], pentru 1 ≤ i < k.
 *
 * Restricții și precizări
 * =======================
 * Dimensiunea minimă a cutiilor este 1, iar cea maximă este 10.
 * Numărul maxim de cutii dintr-o mulțime este 20.
 */

//#define NDEBUG

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXM	20
#define MAXN	10

struct cutii {
	short unsigned int m;		// numărul de cutii (1 ≤ m ≤ MAXM)
	short unsigned int n;		// dimensiune cutii (1 ≤ n ≤ MAXN)
	unsigned int dim[MAXM][MAXN];
	unsigned int *ord[MAXM];	// cutiile ordonate crescător (parțial)
};

// citire mulțime de cutii
bool citire_multime(FILE *fisier, struct cutii *multime);

// ordonare dimensiuni în fiecare cutie din mulțime
void ordonare_dimensiuni(struct cutii *multime);

// ordonare cutii în mulțime doar după primul element
// (sau primele elemente distincte)
void ordonare_cutii(struct cutii *multime);

// determină secvența cea mai lungă de cutii ce încap una în alta
short int secvmax_cutii(struct cutii *multime, short int **secv);

// afișează o secvență de cutii din vectorul secv[k]
// secv[k][0] reprezintă lungimea secvenței și nu face parte din secvență
void afiseaza_cutii(FILE *fisier, struct cutii *multime,
			short int **secv, short int k);

/**
 * Soluție
 * =======
 * Pentru a putea determina computațional dacă o cutie este inclusă
 * în altă cutie, dimensiunile fiecărei cutii sunt permutate a.î.
 * dimeniunile (x1,x2,..xn) să aibă proprietatea x1 < x2 < .. < xn.
 * Am folosit "int" pentru numere întregi generice în limbajul C.
 *
 * Cutiile sunt sortate în funcție de prima dimensiune (cea mai mică
 * după permutare) sau prima dimensiune diferită, adică se obține
 * o secvență completă de cutii c1,c2,..cm cu proprietatea că c[i]
 * are prima dimensiune mai mică sau egală cu prima dimensiune c[i+1],
 * pentru 1 ≤ i < m.
 * În caz de egalitate la prima dimensiune se înaintează până la prima
 * dimensiune diferită (sau cutiile sunt identice).
 *
 * Se calculează toate secvențele posibile de cutii c1,c2,..ck ce pot
 * fi incluse una în alta. Dintre acestea doar secvența cu cea mai mare
 * lungime de cutii este scrisă în fișierul de ieșire.
 *
 * Observație: pentru depanare se comentează declarea macroului NDEBUG
 */
int main(void)
{
	FILE *fintrare;				// "r" din «cutii.in»
	FILE *fiesire;				// "w" în «cutii.out»
	struct cutii mult;			// o singură structură de lucru
	short int *secv[MAXM];			// vector de secvențe cutii
	short int k;				// numărul maxim de secvențe
	short int i;

	fintrare = fopen("cutii.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «cutii.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("cutii.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «cutii.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	for (k = 0; k < MAXM; k++) {
		// secvența cea mai lungă conține toate cutiile
		secv[k] = malloc(sizeof(short int) * (MAXM+1));
		if (NULL == secv[k]) {
			fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul secv[%hi]\n", k);
			return errno;
		}
	}

	// dacă fișierul de intrare este gol, bucla nu se execută deloc
	for (i = 1; citire_multime(fintrare, &mult); i++) {
#ifndef NDEBUG
		if (1 != i)
			fputc('\n', stdout);
		fprintf(stdout, "########## mulțimea de cutii nr. «%hi» ##########\n", i);
#endif
		ordonare_dimensiuni(&mult);
		ordonare_cutii(&mult);		// doar după primul element
		k = secvmax_cutii(&mult, secv);
		afiseaza_cutii(fiesire, &mult, secv, k);
	}
	return 0;
}

// COMPLEXITATE Θ(m·n)
bool citire_multime(FILE *fisier, struct cutii *multime)
{
	int i, j;

	// citesc numărul de cutii «m» și dimensiune cutii «n»
	if (2 != fscanf(fisier, "%hu %hu", &multime->m, &multime->n))
		return false;			// eroare de citire sau sfârșit de fișier

	for (i = 0; i < multime->m; i++)		// index cutie
		for (j = 0; j < multime->n; j++)	// dimensiune cutii
			if (1 != fscanf(fisier, "%u", &multime->dim[i][j]))
				return false;
	return true;
}

// COMPLEXITATE timp Θ(m·n²) | spațiu Θ(m·n)
void ordonare_dimensiuni(struct cutii *multime)
{
	int k, i, j;
	unsigned int cheie;
	unsigned int *cutie;

	for (k = 0; k < multime->m; k++) {		// index cutie
		cutie = multime->dim[k];
		// sortare prin inserție
		for (j = 1; j < multime->n; j++) {	// dimensiune cutii
			cheie = cutie[j];
			for (i = j-1; i >= 0 && cutie[i] > cheie; i--)
				cutie[i+1] = cutie[i];
			cutie[i+1] = cheie;
		}
	}
}

// COMPLEXITATE timp Θ(m²) | spațiu Θ(m)
void ordonare_cutii(struct cutii *multime)
{
	int i, j, k;
	unsigned int *cheie;

	// inițializare vector de pointeri
	for (i = 0; i < multime->m; i++)
		multime->ord[i] = multime->dim[i];

	// ordonare pointeri cutii prin inserție
	for (j = 1; j < multime->m; j++) {		// index cutie
		cheie = multime->ord[j];
		for (i = j-1; i >= 0; i--) {
			// CAPCANĂ: primele dimensiunile sunt egale
			for (k = 0; k < multime->n; k++)
				// avansez până la prima dimensiune diferită
				if (multime->ord[i][k] != cheie[k])
					break;
			if (k == multime->n)		// avem două cutii identice
				break;
			if (multime->ord[i][k] > cheie[k])
				multime->ord[i+1] = multime->ord[i];
			else
				break;		// cutiile rămase sunt "≤"
		}
		multime->ord[i+1] = cheie;
	}
}

// COMPLEXITATE Θ(n)
bool cutie_inclusa(struct cutii *multime, int c1, int c2)
{
	int i;
	unsigned int *v1, *v2;

	v1 = multime->ord[c1];				// vector dimensiuni c1
	v2 = multime->ord[c2];				// vector dimensiuni c2

	// determină dacă prima cutie este inclusă în cealaltă (c1 ⊂ c2)
	for (i = 0; i < multime->n; i++)
		if (v1[i] >= v2[i])
			return false;
	return true;
}

// crează o nouă secvență de cutii «nrsecv» ce conține rădăcina «r»
// COMPLEXITATE Θ(r)
void crsecv_cutii(struct cutii *multime, short int **secv,
			short int *nrsecv, short int r)
{
	short int i;
	short int u;			// index ultima cutie din secvență
	short int *k;			// numărul de cutii în secv «nrsecv»

#ifndef NDEBUG
	int cr, ci, cu;			// număr de cutie corespunzător lui r, i, u
	cr = (int)((multime->ord[r] - multime->dim[0])/MAXN + 1);
	fprintf(stdout, "I: inițiez crearea secvenței %i cu rădăcina %hi\n", *nrsecv, cr);
#endif
	k = secv[*nrsecv];
	*k = 0;				// inițial nu avem nici o cutie
	for (u = 0, i = 0; i < r; i++) {	// index cutie
#ifndef NDEBUG
		ci = (int)((multime->ord[i] - multime->dim[0])/MAXN + 1);
#endif
		// toate cutiile de la începutul secvenței trebuie să fie
		// incluse în cutia rădăcină (i ⊂ r)
		if (!cutie_inclusa(multime, i, r)) {
#ifndef NDEBUG
			fprintf(stdout, "I: - cutia %i nu este inclusă în cutia %i\n", ci, cr);
#endif
			continue;
		}

		// compar cutia «i» cu ultima cutie «k»
		if ((0 != *k) && (u != i) && !cutie_inclusa(multime, u, i)) {
#ifndef NDEBUG
			cu = (int)((multime->ord[u] - multime->dim[0])/MAXN + 1);
			fprintf(stdout, "I: - cutia %i nu este inclusă în cutia %i\n", cu, ci);
#endif
			continue;
		}

#ifndef NDEBUG
		fprintf(stdout, "I: + cutia %hi este adaugată la secv[%hi] (r%hi)\n", ci, *nrsecv, cr);
#endif
		// adaug cutia «i» la secvența «nrsecv»
		(*k)++;
		secv[*nrsecv][*k] = i;
		u = i;				// ultima cutie adăugată
	}

#ifndef NDEBUG
	fprintf(stdout, "I: + cutia %i este adaugată la secv[%hi] (r%i)\n", cr, *nrsecv, cr);
#endif
	// adaug cutia rădăcină «r» la sfârșitul secvenței «nrsecv»
	(*k)++;
	secv[*nrsecv][*k] = r;
	(*nrsecv)++;				// o secvență mai mult
}

// COMPLEXITATE Θ(m·s), unde «s» este numărul total de secvențe
short int secvmax_cutii(struct cutii *multime, short int **secv)
{
	short int i, j, u;
	short int *k;				// numărul de cutii ↦ secv[?][0]
	short int nrsecv, max;
	bool adaugat;				// a fost cutia adăugată la una
						// din secvențele existente?
#ifndef NDEBUG
	int ci;
#endif

	nrsecv = 0;				// numărul total de secvențe
	for (i = 0; i < multime->m; i++) {	// index cutie
		adaugat = false;
		for (j = 0; j < nrsecv; j++) {	// index secvență
			k = secv[j];		// numărul de cutii în secv «j»
			u = secv[j][*k];	// ultima cutie în secvența «j»
			if (cutie_inclusa(multime, u, i)) {
#ifndef NDEBUG
				ci = (int)((multime->ord[i] - multime->dim[0])/MAXN + 1);
				fprintf(stdout, "I: + cutia %i este adaugată la secv[%hi]\n", ci, j);
#endif
				// adaug cutia «i» la secvența «j»
				(*k)++;
				secv[j][*k] = i;
				adaugat = true;
			}
		}
		if (!adaugat)
			crsecv_cutii(multime, secv, &nrsecv, i);
	}

#ifndef NDEBUG
	fprintf(stdout, "I: au fost găsite «%hi» secvențe de cutii distincte\n", nrsecv);
#endif
	// caut secvența de cutii cea mai lungă
	for (j = 0, i = 0; i < nrsecv; i++) {
		if (j < secv[i][0]) {
			j = secv[i][0];		// numărul de cutii
			max = i;		// indexul secvenței
		}
#ifndef NDEBUG
		afiseaza_cutii(stdout, multime, secv, i);
	}
	fprintf(stdout, "I: secvența de cutii cea mai lungă: secv[%hi], cutii = %hi\n", max, secv[max][0]);

	fprintf(stdout, "\nI: afișare cutii sortate parțial după prima dimensiune\n");
	for (i = 0; i < multime->m; i++) {
		fprintf(stdout, "%i:", (int)((multime->ord[i] - multime->dim[0])/MAXN + 1));
		for (j = 0; j < multime->n; j++)
			fprintf(stdout, " %u", multime->ord[i][j]);
		fputc('\n', stdout);
#endif
	}
	return max;
}

// COMPLEXITATE Θ(|S|), unde |S| ≤ m este cardinalul celei mai lungi secvențe
void afiseaza_cutii(FILE *fisier, struct cutii *multime,
				short int **secv, short int k)
{
	int i, j;

	// scriu numărul de cutii pe prima linie
	fprintf(fisier, "%hi\n", secv[k][0]);

	// scriu prima cutie din secvență în fișierul de ieșire
	// (este necesar pentru a nu scrie un «SPACE» la început de linie)
	j = (int)((multime->ord[secv[k][1]] - multime->dim[0])/MAXN + 1);
	fprintf(fisier, "%i", j);

	// scriu restul de cutii din secvență în fișierul de ieșire
	for (i = 2; i <= secv[k][0]; i++) {
		j = (int)((multime->ord[secv[k][i]] - multime->dim[0])/MAXN + 1);
		fprintf(fisier, " %i", j);
	}
	fputc('\n', fisier);
}
