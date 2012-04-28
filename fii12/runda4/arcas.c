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
int cast[MAXTINTE];			// arcași câștigători
int perd[MAXTINTE];			// arcași perdanți

// citesc dimensiuni și rangurile tuturor arcașilor
int citire_arcasi(FILE *fisier);

#ifndef NDEBUG
// afișare ranguri arcași în ordinea de start
void afisare_arcasi(void);

// afișare ranguri arcași în runda curentă
void afisare_runda(int runda);
#endif

// alinierea arcașilor la linia de start: inițializare cast[], perd[]
void aliniere_start(int tinta);

// calculează poziția arcașului dacă se pleacă de la ținta specificată
int calc_pozitie(void);

// COMPLEXITATE timp O(n³) | spațiu θ(n)
int main(void)
{
	FILE *fintrare;				// "r" din «arcas.in»
	FILE *fiesire;				// "w" în «arcas.out»
	int tmax;				// ținta de plecare pentru pmin
	int pmin;				// poziția minimă (nr. țintă)
	int t, p;

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
	afisare_arcasi();
#endif

	// probez toate țintele pentru cea mai bună performanță
	for (pmin = MAXTINTE*2, t = 1; t <= nt; ++t) {
		aliniere_start(t);
		p = calc_pozitie();

		// actualizare ținta de start pentru performanța maximă
		if (p <= pmin) {
			tmax = t;
			pmin = p;
#ifndef NDEBUG
			printf("- ținta start #%d ↦ poziția %d\n", t, p);
#endif
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
void afisare_runda(int runda)
{
	int *ac, *ap, i;

	printf("-- runda #%d --\n", runda);
	for (i = 1, ac = cast, ap = perd; i <= nt; ++i, ++ac, ++ap)
		printf("tinta#%d: %d ∘ %d\n", i, *ac, *ap);
}
#endif

// COMPLEXITATE θ(n)
void aliniere_start(int tinta)
{
	int i, j;

	// aliniere arcași poziționați înaintea arcașului tău
	--tinta;				// 1 ≤ tinta ≤ N
	for (i = 0, j = 1; i < tinta; ++i, ++j)
		if (arcasi[j] < arcasi[j+1]) {
			cast[i] = arcasi[j];
			perd[i] = arcasi[++j];
		} else {
			perd[i] = arcasi[j];
			cast[i] = arcasi[++j];
		}

	// așez arcașul tău la țintă
	if (arcasi[0] < arcasi[j]) {
		cast[i] = arcasi[0];
		perd[i] = arcasi[j];
	} else {
		perd[i] = arcasi[0];
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
int calc_pozitie(void)
{
	int ultim;				// ultimul arcaș în poziția finală
	int i, j, r1;
	int nrrunda, pozitie;

	if ((1 == arcasi[0]) || (1 == nt))	// arcașul cu rang «1»
		return 1;
	nrrunda = 0;
	ultim = 2 * nt;
	while ((1 != perd[0]) || (ultim > nt + 1)) {
		++nrrunda;
		r1 = cast[0];			// salvez rangul perdantului #1
		// permutări [1 … N-1]
		for (i = 0, j = 1; j < nt; ++i, ++j) {
			if (perd[i] > cast[j]) {
				cast[i] = cast[j];
			} else {
				cast[i] = perd[i];
				perd[i] = cast[j];
			}
			if ((ultim == perd[i]) && (0 != i)) {
				if (ultim == arcasi[0]) {
#ifndef NDEBUG
//					printf("arcaș codaș rang#%d, la runda «%d» are ținta #%d\n", ultim, nrrunda, (i+1));
#endif
					return (i + 1);
				}
				--ultim;
			}
		}
		// perdantul «ultim» la ținta N?
		if (ultim == perd[i])
			--ultim;

		// excepția locului întâi: câștigătorul rămâne la prima țintă
		if (cast[0] < perd[0]) {
			j = cast[0];
			cast[0] = perd[0];
			perd[0] = j;
		}

		// pierzătorul de la ținta «1» se mută la ținta «N»
		assert(i == nt - 1);
		if (perd[i] > r1) {
			cast[i] = r1;
		} else {
			cast[i] = perd[i];
			perd[i] = r1;
		}
#ifndef NDEBUG
//		afisare_runda(nrrunda);
//		printf("ultim = %d\n\n", ultim);
#endif
	};
	// arcașii codași au fost eliminați până la runda curentă
	assert(arcasi[0] <= nt + 1);

	// arcaș fruntaș (printre primii N+1)
	for (i = 0; i < nt; ++i)
		if (arcasi[0] == cast[i])
			break;
	pozitie = i + 1;			// număr țintă
#ifndef NDEBUG
//	printf("arcaș fruntaș rang#%d, la runda «%d» are ținta #%d\n", cast[i], nrrunda, pozitie);
#endif
	pozitie -= (nr - nrrunda) % nt;		// T - (R % N)
	if (pozitie <= 0)
		pozitie += nt;
#ifndef NDEBUG
//	printf("arcaș fruntaș rang#%d, la runda «%d» are ținta #%d\n", cast[i], nr, pozitie);
#endif
	return pozitie;
}
