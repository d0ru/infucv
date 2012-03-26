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

// afișare listă de adiacență
void fafisare_gnla(FILE *fisier, const struct nod varf[], int nrvarf)
{
	int i;
	struct nod *pn;

	for (i = 0; i < nrvarf; i++) {
		fprintf(fisier, "%d:", varf[i].nr);
		pn = varf[i].urm;
		while (NULL != pn) {
			fprintf(fisier, " %d", pn->nr);
			pn = pn->urm;
		}
		fputc('\n', fisier);
	}
}

// returnează numărul de vecini ai nodului dat
// (1 ≤ nod ≤ nrvarf)
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
// (1 ≤ nod ≤ nrvarf)
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
// (1 ≤ nod1 < nod2 ≤ nrvarf)
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


// afisare componenta conexă de la «nod» cu parcurgere în lățime
// (1 ≤ nod ≤ nrvarf)
void afcclatviz_gnla(const struct nod varf[], int nrvarf, int nod, bool *vizitat)
{
	int i, k;
	queue<int> qi;
	bool gasit;
	struct nod *pn;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	if (vizitat[nod])			// nu ar trebui să fie apelat
		return;
	vizitat[nod] = true;
	qi.push(nod);				// Q <= nod
	printf("   %d", nod+1);			// CALL vizitare(nod)

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
}

// afișare componente conexe folosind parcurgerea în lățime
void afcclat_gnla(const struct nod varf[], int nrvarf)
{
	int cc, nod;
	bool *vizitat;

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	printf("Afișare componente conexe GNLA folosind parcurgerea în lățime!\n");
	cc = 1;
	for (nod = 0; nod < nrvarf;) {
		if (vizitat[nod++])
			continue;
		printf("Componenta conexă «%d» începe cu nodul %d:\n", cc++, nod);
		afcclatviz_gnla(varf, nrvarf, nod, vizitat);
	}
	free(vizitat);
}

// parcurgere/vizitare în lățime (BFS)
// (1 ≤ nod ≤ nrvarf)
void vizlat_gnla(const struct nod varf[], int nrvarf, int nod)
{
	bool *vizitat;

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	afcclatviz_gnla(varf, nrvarf, nod, vizitat);
	free(vizitat);
}


// afisare componenta conexă de la «nod» cu parcurgere în adâncime
// (1 ≤ nod ≤ nrvarf)
void afccadviz_gnla(const struct nod varf[], int nrvarf, int nod, bool *vizitat)
{
	int i, k, adancime;
	stack<int> si;
	bool cap, gasit, primul;
	struct nod *pn;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	if (vizitat[nod])			// nu ar trebui să fie apelat
		return;
	vizitat[nod] = true;
	si.push(nod);				// S <= nod
	printf("   %d", nod+1);			// CALL vizitare(nod)
	adancime = 2;				// primul în ierarhie

	cap = true;				// s-a afișat capul componentei conexe
	gasit = false;				// dacă vârful curent mai are vecini nevizitați
	primul = false;				// ramură nouă?
	while (!si.empty()) {			// S ≠ ∅
		if (!gasit) {
			k = si.top();		// S => k
			si.pop();
			adancime--;
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
			if (primul && !cap)
				printf("\n%*c", 4*adancime, ' ');
			else
				cap = false;		// la următoarele se afișează linie nouă cu indentare
			printf(" → %d", pn->nr);	// CALL vizitare(i)
			k = i;
			adancime++;
			primul = false;
			gasit = true;
			break;			// am găsit cel puțin un vârf nevizitat adiacent cu k
		}
	}
	putchar('\n');
}

// afișare componente conexe folosind parcurgerea în adâncime
void afccad_gnla(const struct nod varf[], int nrvarf)
{
	int cc, nod;
	bool *vizitat;

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	printf("Afișare componente conexe GNLA folosind parcurgerea în adâncime!\n");
	cc = 1;
	for (nod = 0; nod < nrvarf;) {
		if (vizitat[nod++])
			continue;
		printf("Componenta conexă «%d» începe cu nodul %d:\n", cc++, nod);
		afccadviz_gnla(varf, nrvarf, nod, vizitat);
	}
	free(vizitat);
}

// parcurgere/vizitare în adâncime (DFS)
// (1 ≤ nod ≤ nrvarf)
void vizad_gnla(const struct nod varf[], int nrvarf, int nod)
{
	bool *vizitat;

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	afccadviz_gnla(varf, nrvarf, nod, vizitat);
	free(vizitat);
}
