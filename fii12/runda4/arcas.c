/**
 * Soluție
 * -------
 * Avem două rânduri de arcași, rândul câștigătorilor și cel al perdanților.
 * Pe primul rând se face o permutare la stânga la fiecare rundă. Rândul
 * al doilea rămâne neschimbat.
 * Excepția este ținta «1» unde rangurile arcașilor sunt inversate.
 *
 * Se calculează poziția finală a arcașului pentru fiecare țintă de start.
 * ------
 * Pentru a reduce numărul de operații, se determină care este ultimul arcaș
 * ce poate avansa. Din start arcașul cu rangul «2•N» este în poziția finală
 * (cu excepția situației când la start se află la ținta #1, imediat la prima
 * rundă este mutat la ținta #N).
 *
 * În al doilea rând, după cel mult «N-1» runde toți arcașii cu un rang cuprins
 * între «N+2» și «2•N» sunt așezați pe poziția lor finală (nu mai pot avansa),
 * iar arcașul cu rangul «1» va fi pe poziția «1» finală.
 *   2 3 … … … N N+1 — dar într-o ordine aleatoare în funcție de start
 *   1 X X X X X  X  — ranguri arcași ce nu mai pot avansa în concurs
 *
 * Poziția finală este calculată cu formula «T - (R % N)», unde «T» este ținta
 * curentă, iar «R» este numărul de runde rămase până la sfârșitul competiției.
 *
 * Cazuri posibile
 * ---------------
 * 1) arcașul tău are rangul #1 ↦ poziția N
 * 2) arcașul tău are rangul #N ↦ poziția finală după prima rundă
 * 3) arcașul tău are un rang codaș ↦ poziția finală după maxim «N-1» runde
 * 4) arcașul tău are un rang fruntaș ↦ se aplică formula de mai sus
 *
 * Teste extreme
 * -------------
 * 1) N=1, R=2
 * 2) N=1, R=1000000000
 * 3) N=200000, R=200000
 * 4) N=200000, R=1000000000
 */

//#define NDEBUG

#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define MAXTINTE	200000

int nt;					// numărul de ținte
int nr;					// numărul de runde

int arcasi[MAXTINTE * 2];		// ranguri arcași
int arcasu;
int cast[MAXTINTE * 2];			// arcași câștigători
int perd[MAXTINTE];			// arcași perdanți

// citesc dimensiuni și rangurile tuturor arcașilor
int citire_arcasi(FILE *fisier);

#ifndef NDEBUG
// afișare ranguri arcași în ordinea de start
void afisare_arcasi(void);

// afișare ranguri arcași în runda curentă
void afisare_runda(int prim, int runda);
#endif

// alinierea arcașilor la linia de start: inițializare cast[], perd[]
void aliniere_start(int tinta);

// calculează poziția arcașului dacă se pleacă de la ținta specificată
int calc_pozitie_codas(void);
int calc_pozitie_fruntas(void);

// COMPLEXITATE timp O(n³) | spațiu θ(n)
int main(void)
{
	FILE *fintrare;				// "r" din «arcas.in»
	FILE *fiesire;				// "w" în «arcas.out»
	int tmax;				// ținta de plecare pentru pmin
	int pmin;				// poziția minimă (nr. țintă)
	int t, p, up;

	fintrare = fopen("arcas.in", "r");
	if (NULL == fintrare) {
		fprintf(stderr, "E: fișierul «arcas.in» nu a putut fi deschis pentru citire\n");
		return errno;
	}

	fiesire = fopen("arcas.out", "w");
	if (NULL == fiesire) {
		fprintf(stderr, "E: fișierul «arcas.out» nu a putut fi deschis pentru scriere\n");
		return errno;
	}

	t = citire_arcasi(fintrare);
	if (0 != t)
		return t;			// errno
#ifndef NDEBUG
//	afisare_arcasi();
#endif

	// arcașul cu rang «1» sau doar o țintă
	if ((1 == arcasu) || (1 == nt)) {
		fprintf(fiesire, "1");
		return 0;
	}

	// optimizez căutarea în funcție de rangul arcașului tău
	if (arcasu <= nt + 1) {
		up = 1;
		for (p = 0, pmin = nt*2, t = 1; t <= nt; ++t) {
			aliniere_start(t);
#ifndef NDEBUG
//			printf("====== ținta #%d ======\n", t);
#endif
			p = calc_pozitie_fruntas();
#ifndef NDEBUG
			printf("- ținta start #%d ↦ poziția %d (%+d de la %d)\n", t, p, p-up < 0 ? nt+p-up : p-up, up);
#endif

			up = p;
			// actualizare ținta de start pentru performanța maximă
			if (p <= pmin) {
				tmax = t;
				pmin = p;
			}
		}
	} else {
		for (p = 0, pmin = nt*2, t = 2; t <= nt; ++t) {
			aliniere_start(t);
			p = calc_pozitie_codas();
#ifndef NDEBUG
			printf("- ținta start #%d ↦ poziția %d\n", t, p);
#endif

			// actualizare ținta de start pentru performanța maximă
			if (p <= pmin) {
				tmax = t;
				pmin = p;
			} else
				break;
		}
	}

	fprintf(fiesire, "%d", tmax);
	return 0;
}

// COMPLEXITATE timp θ(n) | spațiu θ(n)
int citire_arcasi(FILE *fisier)
{
	int *arcas, i, na;

	// citesc numărul de ținte și runde
	if (2 != fscanf(fisier, "%d %d", &nt, &nr))
		return errno;			// eroare de citire
	na = 2 * nt;				// număr arcași
#ifndef NDEBUG
	printf("nt=%d, na=%d, nr=%d\n", nt, na, nr);
#endif

	for (i = 0, arcas = arcasi; i < na; ++i, ++arcas)
		fscanf(fisier, "%d", arcas);
	arcasu = arcasi[0];
	return 0;
}

#ifndef NDEBUG
// COMPLEXITATE θ(n)
void afisare_arcasi(void)
{
	int *arcas, i, na;

	printf("Start:");
	na = 2 * nt;				// număr arcași
	for (i = 1, arcas = arcasi; i <= na; ++i, ++arcas)
		printf(" %d", *arcas);
	putchar('\n');
}

// COMPLEXITATE θ(n)
void afisare_runda(int prim, int runda)
{
	int *ac, *ap, i;

	printf("-- runda #%d --\n", runda);
	for (ac = cast+prim, ap = perd, i = 1; i <= nt; ++i, ++ac, ++ap)
		printf("tinta#%d: %d ∘ %d\n", i, *ac, *ap);
}
#endif

// COMPLEXITATE θ(n)
void aliniere_start(int tinta)
{
	int i, j;

	--tinta;				// 1 ≤ tinta ≤ N
	// aliniere arcași poziționați înaintea arcașului tău
	for (i = 0, j = 1; i < tinta; ++i, ++j)
		if (arcasi[j] < arcasi[j+1]) {
			cast[i] = arcasi[j];
			perd[i] = arcasi[++j];
		} else {
			perd[i] = arcasi[j];
			cast[i] = arcasi[++j];
		}

	// așez arcașul tău la țintă
	if (arcasu < arcasi[j]) {
		cast[i] = arcasu;
		perd[i] = arcasi[j];
	} else {
		perd[i] = arcasu;
		cast[i] = arcasi[j];
	}

	// aliniere arcași poziționați după arcașul tău
	for (i = tinta+1, ++j; i < nt; ++i, ++j)
		if (arcasi[j] < arcasi[j+1]) {
			cast[i] = arcasi[j];
			perd[i] = arcasi[++j];
		} else {
			perd[i] = arcasi[j];
			cast[i] = arcasi[++j];
		}

	// excepția locului întâi: câștigătorul rămâne la prima țintă
	i = cast[0];
	cast[0] = perd[0];
	perd[0] = i;
}

// COMPLEXITATE O(n²)
int calc_pozitie_codas(void)
{
	int ultim;				// ultimul arcaș în poziția finală
	int k, p, r, s, prim;

	// caut doar un arcaș codaș (vectorul perd[])
	assert(arcasu > nt + 1);

	r = 0;					// nr. rundei curente
	prim = 0;				// început vector cast[]
	ultim = 2 * nt;
	do {
		++r;
		// pierzătorul de la ținta «1» se mută la ținta «N»
		cast[prim + nt] = cast[prim];	// permutări [1 … N-1]

		// este nevoie de o interschimbare cast[] ↔ perd[]?
		for (p = 1, k = ++prim+1; p < nt; ++p, ++k) {
			if (cast[k] > perd[p]) {
				s = cast[k];
				cast[k] = perd[p];
				perd[p] = s;
			}
			if (ultim == perd[p])
				--ultim;
		}

		// excepția locului întâi: câștigătorul rămâne la prima țintă
		if (cast[prim] < perd[0]) {
			s = cast[prim];
			cast[prim] = perd[0];
			perd[0] = s;
		}
#ifndef NDEBUG
//		afisare_runda(prim, r);
//		printf("ultim = %d\n\n", ultim);
#endif
	} while (ultim >= arcasu);
	// maxim N-1 operații?
	assert(prim <= nt);

	// arcaș codaș (printre ultimii N-1)
	for (p = 1; p < nt; ++p)
		if (arcasu == perd[p])
			break;
	assert(1 != arcasu);
	assert(p < nt);
	++p;					// număr țintă
#ifndef NDEBUG
//	afisare_runda(prim, r);
//	printf("arcaș codaș rang#%d, la runda «%d» are ținta #%d\n", arcasu, r, p);
#endif
	return p;
}

// COMPLEXITATE O(n²)
int calc_pozitie_fruntas(void)
{
	int ultim;				// ultimul arcaș în poziția finală
	int k, p, r, s, prim;

	// caut doar un arcaș fruntaș (vectorul cast[])
	assert(arcasu <= nt + 1);

#ifndef NDEBUG
//	afisare_runda(0, 0);
#endif
	r = 0;					// nr. rundei curente
	prim = 0;				// început vector cast[]
	ultim = 2 * nt;
	do {
		++r;
		// pierzătorul de la ținta «1» se mută la ținta «N»
		cast[prim + nt] = cast[prim];	// permutări [1 … N-1]

		// este nevoie de o interschimbare cast[] ↔ perd[]?
		for (p = 1, k = ++prim+1; p < nt; ++p, ++k) {
			if (cast[k] > perd[p]) {
				s = cast[k];
				cast[k] = perd[p];
				perd[p] = s;
			}
			if (ultim == perd[p])
				--ultim;
		}

		// excepția locului întâi: câștigătorul rămâne la prima țintă
		if (cast[prim] < perd[0]) {
			s = cast[prim];
			cast[prim] = perd[0];
			perd[0] = s;
		}
#ifndef NDEBUG
//		afisare_runda(prim, r);
//		printf("ultim = %d\n\n", ultim);
#endif
	} while ((1 != perd[0]) || (ultim > nt + 1));
	// maxim N-1 operații?
	assert(prim <= nt);

	// arcaș fruntaș (printre primii N+1)
	for (k = 0; k < nt; ++k)
		if (arcasu == cast[prim+k])
			break;
	assert(1 != arcasu);
	assert(k < nt);
	++k;					// număr țintă
#ifndef NDEBUG
//	afisare_runda(prim, r);
//	printf("arcaș fruntaș rang#%d, la runda «%d» are ținta #%d\n", arcasu, r, k);
#endif
	k -= (nr - r) % nt;			// T - (R % N)
	if (k <= 0)
		k += nt;
#ifndef NDEBUG
//	printf("arcaș fruntaș rang#%d, la runda «%d» are ținta #%d\n\n", arcasu, nr, k);
#endif
	return k;
}
