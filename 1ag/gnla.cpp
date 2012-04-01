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

// COMPLEXITATE timp Θ(n+m) | spațiu Θ(n+m)
struct nod *fcitire_gnla(FILE *fisier, int *nrvarf)
{
	int u, v;
	struct nod *graf;			// vectorul nodurilor
	struct nod *elem;

	if (1 != fscanf(fisier, "%i", nrvarf))
		return NULL;

	if (*nrvarf <= 0) {
		fprintf(stderr, "E: numărul de noduri «%d» trebuie să fie pozitiv!\n", *nrvarf);
		return NULL;
	}

	graf = (struct nod *) malloc(sizeof(struct nod) * (*nrvarf));	// |V|
	if (NULL == graf) {
		fprintf(stderr, "E: nu s-a putut aloca memorie pentru vectorul nodurilor!\n");
		return NULL;
	}

	for (v = 0; v < *nrvarf; v++) {			// numărul de linii la intrare poate fi mai mic decât
							// numărul nodurilor din graf
		graf[v].nr = 0;				// rămâne 0 doar dacă nu există o linie ^v: la intrare
		graf[v].urm = NULL;			// rămâne NULL dacă nu are nici un vecin
	}

	while (1 == fscanf(fisier, "%i:", &v)) {
		if (v < 1 || v > *nrvarf) {
			fprintf(stderr, "E: număr de nod «%d» incorect, 1 ≤ v ≤ %d!\n", v, *nrvarf);
			while (EOF != (u = fgetc(fisier)))
				if ('\n' == u)		// ignoră tot până la sfârșit de linie
					break;
			continue;
		}
		graf[v-1].nr = v;			// numerotare vector de la zero

		elem = graf + v - 1;			// elementele sunt introduse în ordinea dată
		fscanf(fisier, "%d", &u);		// lista de vecini îl are cel puțin pe 0
		while (u > 0) {
			elem->urm = (struct nod *) malloc(sizeof(struct nod));
			if (NULL == elem->urm) {
				fprintf(stderr, "E: nu s-a putut aloca memorie pentru vecinul «%d» al nodului «%d»!\n", u, v);
				continue;
			}
			elem = elem->urm;		// avansez în listă
			elem->nr = u;
			elem->urm = NULL;		// inițializare în caz că este ultimul element
			fscanf(fisier, "%d", &u);	// citesc următorul vecin al lui v
		}

		while (EOF != (u = fgetc(fisier)))	// ignoră tot până la sfârșit de linie
			if ('\n' == u)
				break;
	}
	return graf;
}

// COMPLEXITATE timp Θ(n+m) | spațiu Θ(n+m)
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

// COMPLEXITATE Θ(m)#n
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

// COMPLEXITATE Θ(m)#n
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

// COMPLEXITATE Θ(m)#n
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


// COMPLEXITATE Θ(m)#c
void afcclatviz_gnla(const struct nod graf[], int nrvarf, int nod, bool *vizitat)
{
	int i, k;
	queue<int> qi;
	bool gasit;
	struct nod *elem;

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
		elem = graf[k].urm;		// parcurg lista de vecini ai lui «k»
		while (NULL != elem) {
			i = elem->nr - 1;	// nodurile încep de la 1, nu de la 0
			if (vizitat[i]) {	// nodul a fost deja vizitat
				elem = elem->urm;
				continue;
			}
			vizitat[i] = true;
			qi.push(i);			// Q <= i
			printf(" → %d", elem->nr);	// CALL vizitare(i)
			gasit = true;
			elem = elem->urm;
		}
		if (gasit)
			putchar('\n');
	}
}

// COMPLEXITATE Θ(n+m)
void afcclat_gnla(const struct nod graf[], int nrvarf)
{
	int cc, nod;
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	printf("Afișare componente conexe GNLA folosind parcurgerea în lățime!\n");
	for (cc = 0, nod = 0; nod < nrvarf;) {
		if (vizitat[nod++])
			continue;
		printf("Componenta conexă «%d» începe cu nodul %d:\n", ++cc, nod);
		afcclatviz_gnla(graf, nrvarf, nod, vizitat);
	}
	free(vizitat);
}

// COMPLEXITATE Θ(n+m)#c
void vizlat_gnla(const struct nod graf[], int nrvarf, int nod)
{
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	afcclatviz_gnla(graf, nrvarf, nod, vizitat);
	free(vizitat);
}


// COMPLEXITATE Θ(m)#c
void afccadviz_gnla(const struct nod graf[], int nrvarf, int nod, bool *vizitat)
{
	int i, k, adancime;
	stack<int> si;
	bool cap, gasit, primul;
	struct nod *elem;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	if (vizitat[nod])			// nu ar trebui să fie apelat
		return;
	vizitat[nod] = true;
	si.push(nod);				// S <= nod
	printf("   %d", nod+1);			// CALL vizitare(nod)
	adancime = 2;				// primul în ierarhie

	cap = true;				// s-a afișat capul componentei conexe
	gasit = false;				// dacă nodul curent mai are vecini nevizitați
	primul = false;				// ramură nouă?
	while (!si.empty()) {			// S ≠ ∅
		if (!gasit) {
			k = si.top();		// S => k
			si.pop();
			adancime--;
			primul = true;
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
			si.push(k);			// S <= k
			if (primul && !cap)
				printf("\n%*c", 4*adancime, ' ');
			else
				cap = false;		// la următoarele se afișează linie nouă cu indentare
			printf(" → %d", elem->nr);	// CALL vizitare(i)
			k = i;
			adancime++;
			primul = false;
			gasit = true;
			break;			// am găsit cel puțin un nod nevizitat adiacent cu k
		}
	}
	putchar('\n');
}

// COMPLEXITATE Θ(n+m)
void afccad_gnla(const struct nod graf[], int nrvarf)
{
	int cc, nod;
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	printf("Afișare componente conexe GNLA folosind parcurgerea în adâncime!\n");
	for (cc = 0, nod = 0; nod < nrvarf;) {
		if (vizitat[nod++])
			continue;
		printf("Componenta conexă «%d» începe cu nodul %d:\n", ++cc, nod);
		afccadviz_gnla(graf, nrvarf, nod, vizitat);
	}
	free(vizitat);
}

// COMPLEXITATE Θ(n+m)#c
void vizad_gnla(const struct nod graf[], int nrvarf, int nod)
{
	bool *vizitat;				// vizitat? A/F

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	afccadviz_gnla(graf, nrvarf, nod, vizitat);
	free(vizitat);
}
