/*
 * Operații pe lista de adiacență a unui graf neorientat.
 * Pentru fiecare nod se reține lista vecinilor săi într-o listă simplu
 * înlânțuită. Capul de listă pentru fiecare nod se reține într-un vector
 * de pointeri către structura «nod».
 *
 * Lista de adiacență se dă în felul următor:
 * nod: listă vecini 0
 */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gn.h"
#include "gnla.h"

#include <queue>
#include <stack>
using namespace std;

// n = |V|, numărul nodurilor grafului neorientat
// m = |E|, numărul muchiilor grafului neorientat
// c, numărul de componente conexe ale grafului neorientat

// COMPLEXITATE timp θ(n+m) | spațiu θ(n+m)
int fcitire_gnla(FILE *fisier, struct nod **graf)
{
	int u, v, nrvarf;
	struct nod *elem;

	if ((1 != fscanf(fisier, "%d", &nrvarf)) || (nrvarf <= 0)) {
		*graf = NULL;
		return -1;
	}

	*graf = (struct nod *) malloc(sizeof(struct nod) * nrvarf);	// |V|
	if (NULL == *graf) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul nodurilor!\n");
		return -1;
	}

	// numărul de linii la intrare poate fi mai mic decât numărul nodurilor din graf
	for (v = 0; v < nrvarf; v++) {
		(*graf)[v].nr = 0;		// rămâne 0 doar dacă nu există o linie ^v: la intrare
		(*graf)[v].urm = NULL;		// rămâne NULL dacă nu are nici un vecin
	}

	while (1 == fscanf(fisier, "%d:", &v)) {
		if (v < 1 || v > nrvarf) {
			fprintf(stderr, "E: număr de nod «%d» incorect, 1 ≤ v ≤ %d!\n", v, nrvarf);
			while (EOF != (u = fgetc(fisier)))
				if ('\n' == u)	// ignoră tot până la sfârșit de linie
					break;
			continue;
		}
		(*graf)[v-1].nr = v;		// numerotare vector de la zero

		elem = *graf + v - 1;		// elementele sunt introduse în ordinea dată
		fscanf(fisier, "%d", &u);	// lista de vecini îl are cel puțin pe 0
		while (u > 0) {
			elem->urm = (struct nod *) malloc(sizeof(struct nod));
			if (NULL == elem->urm) {
				fprintf(stderr, "E: nu s-a putut aloca memorie pentru vecinul «%d» al nodului «%d»!\n", u, v);
				continue;
			}
			elem = elem->urm;
			elem->nr = u;
			elem->urm = NULL;
			fscanf(fisier, "%d", &u);
		}

		// ignoră tot până la sfârșit de linie
		while (EOF != (u = fgetc(fisier)))
			if ('\n' == u)
				break;
	}
	return nrvarf;
}

// COMPLEXITATE timp θ(n+m) | spațiu θ(n+m)
void fafisare_gnla(FILE *fisier, const struct nod graf[], int nrvarf)
{
	int i;
	struct nod *elem;

	for (i = 0; i < nrvarf; i++) {
		fprintf(fisier, "%d:", graf[i].nr);
		elem = graf[i].urm;
		while (NULL != elem) {
			fprintf(fisier, " %d", elem->nr);
			elem = elem->urm;
		}
		fputc('\n', fisier);
	}
}

// COMPLEXITATE θ(m)#n
int nrvec_gnla(const struct nod graf[], int nrvarf, int nod)
{
	int vecini;
	struct nod *elem;

	vecini = 0;
	elem = graf[nod-1].urm;			// nodurile sunt numărate de la 1, nu de la 0
						// nodurile sunt ordonate crescător în vector
	while (NULL != elem) {
		vecini++;
		elem = elem->urm;
	}
	return vecini;
}

// COMPLEXITATE θ(m)#n
void afvec_gnla(const struct nod graf[], int nrvarf, int nod)
{
	struct nod *elem;

	elem = graf[nod-1].urm;			// nodurile sunt numărate de la 1, nu de la 0
						// nodurile sunt ordonate crescător în vector
	while (NULL != elem) {
		printf(" %d;", elem->nr);
		elem = elem->urm;
	}
	putchar('\n');
}

// COMPLEXITATE θ(m)#n
bool muchie_gnla(const struct nod graf[], int nrvarf, int nod1, int nod2)
{
	struct nod *elem;

	elem = graf[nod1 - 1].urm;		// nodurile sunt numărate de la 1, nu de la 0
						// nodurile sunt ordonate crescător în vector
	while (NULL != elem) {
		if (nod2 == elem->nr)
			return true;
		elem = elem->urm;
	}
	return false;
}

// COMPLEXITATE θ(m)#n ??
int nrmuc_gnla(const struct nod graf[], int nrvarf)
{
	int i, nrmuchii;

	nrmuchii = 0;
	for (i = 1; i <= nrvarf; ++i)
		nrmuchii += nrvec_gnla(graf, nrvarf, i);
	return (nrmuchii / 2);
}


// COMPLEXITATE θ(m)#c
void cclatviz_gnla(const struct nod graf[], int nrvarf, int nod, bool *vizitat, bool afis)
{
	int i, k;
	queue<int> qi;
	bool gasit;
	struct nod *elem;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	if (vizitat[nod])			// nu ar trebui să fie apelat
		return;
	vizitat[nod] = true;
	qi.push(nod);				// Q ← nod
	if (afis)
		printf("   %d", nod+1);		// CALL vizitare(nod)

	while (!qi.empty()) {			// Q ≠ ∅
		k = qi.front();			// Q → k
		qi.pop();
		gasit = false;
		elem = graf[k].urm;		// parcurg lista de vecini ai lui «k»
		while (NULL != elem) {
			i = elem->nr - 1;	// nodurile încep de la 1, nu de la 0
			if (vizitat[i]) {	// nodul a fost deja vizitat
				elem = elem->urm;
				continue;
			}
			vizitat[i] = true;
			qi.push(i);		// Q ← i
			if (afis)		// CALL vizitare(i)
				printf(" → %d", elem->nr);
			gasit = true;
			elem = elem->urm;
		}
		if (afis && gasit)
			putchar('\n');
	}
}

// COMPLEXITATE θ(n+m)
int cclat_gnla(const struct nod graf[], int nrvarf, bool afis)
{
	int cc, nod;
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return 0;

	if (afis)
		printf("Afișare componente conexe GNLA folosind parcurgerea în lățime!\n");
	for (cc = 0, nod = 0; nod < nrvarf;) {
		if (vizitat[nod++])
			continue;
		if (afis)
			printf("Componenta conexă «%d» începe cu nodul %d:\n", ++cc, nod);
		cclatviz_gnla(graf, nrvarf, nod, vizitat, afis);
	}
	free(vizitat);
	return cc;
}

// COMPLEXITATE θ(n+m)#c
void vizlat_gnla(const struct nod graf[], int nrvarf, int nod)
{
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	cclatviz_gnla(graf, nrvarf, nod, vizitat, true);
	free(vizitat);
}


// COMPLEXITATE θ(m)#c
void ccadviz_gnla(const struct nod graf[], int nrvarf, int nod, bool *vizitat, bool afis)
{
	int i, k, adancime;
	stack<int> si;
	bool cap, gasit, primul;
	struct nod *elem;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	if (vizitat[nod])			// nu ar trebui să fie apelat
		return;
	vizitat[nod] = true;

	if (afis) {
		printf("   %d", nod+1);		// CALL vizitare(nod)
		adancime = 2;			// primul în ierarhie
		cap = true;			// s-a afișat capul componentei conexe
		primul = false;			// ramură nouă?
	}

	si.push(nod);				// S ← nod
	gasit = false;				// dacă nodul curent mai are vecini nevizitați
	while (!si.empty()) {			// S ≠ ∅
		if (!gasit) {
			k = si.top();		// S → k
			si.pop();
			if (afis) {
				adancime--;
				primul = true;
			}
		}
		gasit = false;
		elem = graf[k].urm;		// parcurg lista de vecini ai lui «k»
		while (NULL != elem) {
			i = elem->nr - 1;	// nodurile încep de la 1, nu de la 0
			if (vizitat[i]) {	// nodul a fost deja vizitat
				elem = elem->urm;
				continue;
			}
			vizitat[i] = true;
			si.push(k);		// S ← k
			if (afis) {
				if (primul && !cap)
					printf("\n%*c", 4*adancime, ' ');
				else
					// la următoarele se afișează linie nouă cu indentare
					cap = false;
				printf(" → %d", elem->nr);
				adancime++;
				primul = false;
			}
			k = i;
			gasit = true;
			break;			// am găsit cel puțin un nod nevizitat adiacent cu k
		}
	}
	putchar('\n');
}

// COMPLEXITATE θ(n+m)
int ccad_gnla(const struct nod graf[], int nrvarf, bool afis)
{
	int cc, nod;
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return 0;

	if (afis)
		printf("Afișare componente conexe GNLA folosind parcurgerea în adâncime!\n");
	for (cc = 0, nod = 0; nod < nrvarf;) {
		if (vizitat[nod++])
			continue;
		if (afis)
			printf("Componenta conexă «%d» începe cu nodul %d:\n", ++cc, nod);
		ccadviz_gnla(graf, nrvarf, nod, vizitat, afis);
	}
	free(vizitat);
	return cc;
}

// COMPLEXITATE θ(n+m)#c
void vizad_gnla(const struct nod graf[], int nrvarf, int nod)
{
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	ccadviz_gnla(graf, nrvarf, nod, vizitat, true);
	free(vizitat);
}
