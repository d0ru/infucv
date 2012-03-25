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
#include <stdio.h>
#include <stdlib.h>

#include "gnla.h"

#include <queue>
#include <stack>
using namespace std;

// nrvarf = |V|, numărul vârfurilor grafului neorientat
struct nod *fcitire_gnla(FILE *fisier, int *nrvarf)
{
	int u, v;
	struct nod *varf, *coada;

	fscanf(fisier, "%i", nrvarf);
	if (*nrvarf <= 0) {
		fprintf(stderr, "E: numărul de noduri «%d» trebuie să fie pozitiv!\n", *nrvarf);
		return NULL;
	}

	varf = (struct nod *) malloc(sizeof(struct nod) * (*nrvarf));
	if (NULL == varf) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul vârfurilor!\n");
		return NULL;
	}

	for (v = 0; v < *nrvarf; v++) {			// numărul de linii la intrare poate fi mai mic decât
							// numărul nodurilor din graf
		varf[v].nr = 0;				// rămâne 0 doar dacă nu există o linie ^v: la intrare
		varf[v].urm = NULL;			// rămâne NULL dacă nu are nici un vecin
	}

	while (1 == fscanf(fisier, "%i:", &v)) {
		if (v < 1 || v > *nrvarf) {
			fprintf(stderr, "E: număr vârf «%d» incorect, 1 ≤ v ≤ %d!\n", v, *nrvarf);
			while (EOF != (u = fgetc(fisier)))	// ignoră tot până la sfârșit de linie
				if ('\n' == u)
					break;
			continue;
		}
		varf[v-1].nr = v;			// numerotare vector de la zero

		coada = varf + v - 1;			// elementele sunt introduse în ordinea dată
		fscanf(fisier, "%d", &u);		// lista de vecini îl are cel puțin pe 0
		while (u > 0) {
			coada->urm = (struct nod *) malloc(sizeof(struct nod));
			if (NULL == coada->urm) {
				fprintf(stderr, "E: nu s-a putut aloca memorie pentru vecinul «%d» al vârfului «%d»!\n", u, v);
				continue;
			}
			coada = coada->urm;		// avansez în listă
			coada->nr = u;
			coada->urm = NULL;		// inițializare în caz că este ultimul element
			fscanf(fisier, "%d", &u);	// citesc următorul vecin al lui v
		}

		while (EOF != (u = fgetc(fisier)))	// ignoră tot până la sfârșit de linie
			if ('\n' == u)
				break;
	}
	return varf;
}

// afișare la STDOUT
void afisare_gnla(const struct nod varf[], int nrvarf)
{
	int v;
	struct nod *pn;

	for (v = 0; v < nrvarf; v++) {
		printf("%d:", varf[v].nr);
		pn = varf[v].urm;
		while (NULL != pn) {
			printf(" %d", pn->nr);
			pn = pn->urm;
		}
		putchar('\n');
	}
}

// returnează numărul de vecini ai nodului dat
int nrvec_gnla(const struct nod varf[], int nrvarf, int nod)
{
	int vecini;
	struct nod *pn;

	vecini = 0;
	pn = varf[nod-1].urm;			// nodurile sunt numărate de la 1, nu de la 0
						// nodurile sunt ordonate crescător în vector
	while (NULL != pn) {
		vecini++;
		pn = pn->urm;
	}

	return vecini;
}

// afișează toți vecinii nodului dat
void afvec_gnla(const struct nod varf[], int nrvarf, int nod)
{
	struct nod *pn;

	pn = varf[nod-1].urm;			// nodurile sunt numărate de la 1, nu de la 0
						// nodurile sunt ordonate crescător în vector
	while (NULL != pn) {
		printf(" %d;", pn->nr);
		pn = pn->urm;
	}
	putchar('\n');
}

// returnează true dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnla(const struct nod varf[], int nrvarf, int nod1, int nod2)
{
	struct nod *pn;

	pn = varf[nod1 - 1].urm;		// nodurile sunt numărate de la 1, nu de la 0
						// nodurile sunt ordonate crescător în vector
	while (NULL != pn) {
		if (nod2 == pn->nr)
			return true;
		pn = pn->urm;
	}
	return false;
}

// parcurgere în lățime (BFS)
void vizlat_gnla(const struct nod varf[], int nrvarf, int nod)
{
	int i, k;
	queue<int> qi;
	bool *vizitat;				// un vector care reține doar starea vizitat? T/F
	bool gasit;
	struct nod *pn;

	if (nrvarf <= 0)
		return;
	vizitat = (bool *) malloc(sizeof(bool) * nrvarf);
	if (NULL == vizitat)
		return;
	for (i = 0; i < nrvarf; i++)		// inițial toate vârfurile sunt nevizitate
		vizitat[i] = false;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	vizitat[nod] = true;
	qi.push(nod);				// Q <= nod
	printf("   %d\n", nod+1);		// CALL vizitare(nod)

	while (!qi.empty()) {			// Q ≠ ∅
		k = qi.front();			// Q => k
		qi.pop();
		gasit = false;
		pn = varf[k].urm;		// parcurg lista de vecini ai lui «k»
		while (NULL != pn) {
			i = pn->nr - 1;		// nodurile încep de la 1, nu de la 0
			if (vizitat[i]) {	// vârful a fost deja vizitat
				pn = pn->urm;
				continue;
			}
			vizitat[i] = true;
			qi.push(i);			// Q <= i
			printf(" → %d", pn->nr);	// CALL vizitare(i)
			gasit = true;
			pn = pn->urm;
		}
		if (gasit)
			putchar('\n');
	}
	free(vizitat);
}

// parcurgere în adâncime (DFS)
void vizad_gnla(const struct nod varf[], int nrvarf, int nod)
{
	int i, k, adancime;
	stack<int> si;
	bool *vizitat;				// un vector care reține doar starea vizitat? T/F
	bool gasit, primul;
	struct nod *pn;

	if (nrvarf <= 0)
		return;
	vizitat = (bool *) malloc(sizeof(bool) * nrvarf);
	if (NULL == vizitat)
		return;
	for (i = 0; i < nrvarf; i++)		// inițial toate vârfurile sunt nevizitate
		vizitat[i] = false;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	vizitat[nod] = true;
	si.push(nod);				// S <= nod
	printf("   %d", nod+1);			// CALL vizitare(nod)
	adancime = 2;				// primul în ierarhie

	gasit = false;				// dacă vârful curent mai are vecini nevizitați
	primul = false;				// ramură nouă?
	while (!si.empty()) {			// S ≠ ∅
		if (!gasit) {
			k = si.top();		// S => k
			si.pop();
			adancime--;
			if (adancime > 1)
				primul = true;
		}
		gasit = false;
		pn = varf[k].urm;		// parcurg lista de vecini ai lui «k»
		while (NULL != pn) {
			i = pn->nr - 1;		// nodurile încep de la 1, nu de la 0
			if (vizitat[i]) {	// vârful a fost deja vizitat
				pn = pn->urm;
				continue;
			}
			vizitat[i] = true;
			si.push(k);			// S <= k
			if (primul) {
				printf("\n%*c", 4*adancime, ' ');
				primul = false;
			}
			printf(" → %d", pn->nr);	// CALL vizitare(i)
			k = i;
			adancime++;
			gasit = true;
			break;			// am găsit cel puțin un vârf nevizitat adiacent cu k
		}
	}
	putchar('\n');
	free(vizitat);
}
