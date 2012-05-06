/*
 * Operații cu matricea de muchii a unui graf neorientat.
 * Într-o matrice 2x|E| se păstrează lista de muchii.
 *
 * Matricea de muchii se dă în felul următor:
 *   M
 *   u1 u2 ... um
 *   v1 v1 ... vm
 * unde M este numărul total al perechilor de muchii de mai jos, iar
 * (u1,v1), (u2,v2),.. (um,vm) sunt toate muchiile grafului neorientat.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gn.h"
#include "gnmm.h"

#include <queue>
#include <stack>
using namespace std;

// n = |V|, numărul nodurilor grafului neorientat
// m = |E|, numărul muchiilor grafului neorientat
// c, numărul de componente conexe ale grafului neorientat

// COMPLEXITATE timp Θ(m) | spațiu Θ(m)
int fcitire_gnmm(FILE *fisier, int **graf)
{
	int i, m, nrmuchii;
	int *elem;

	if ((1 != fscanf(fisier, "%d", &nrmuchii)) || (nrmuchii <= 0)) {
		*graf = NULL;
		return -1;
	}

	m = nrmuchii * 2;
	*graf = (int *) calloc(m, sizeof(int));	// 2x|E|
	if (NULL == *graf)
		return -1;

	elem = *graf;
	for (i = 0; i < m; i++)
		fscanf(fisier, "%d", elem++);
	return nrmuchii;
}

// COMPLEXITATE timp Θ(m) | spațiu Θ(m)
void fafisare_gnmm(FILE *fisier, const int *graf, int nrmuchii)
{
	int i;

	for (i = 0; i < nrmuchii; i++)
		fprintf(fisier, " %d", graf[i]);
	putchar('\n');
	for (i = 0; i < nrmuchii; i++)
		fprintf(fisier, " %d", graf[nrmuchii + i]);
	putchar('\n');
}

// COMPLEXITATE Θ(m)
int nrvarf_gnmm(const int *graf, int nrmuchii)
{
	int i, m, max;

	m = nrmuchii * 2;
	for (i = 0, max = 1; i < m; i++)
		if (graf[i] > max)
			max = graf[i];
	return max;
}

// COMPLEXITATE Θ(m)
int nrvec_gnmm(const int *graf, int nrmuchii, int nod)
{
	int i, m, vecini;

	m = nrmuchii * 2;
	for (i = 0, vecini = 0; i < m; i++)
		if (graf[i] == nod)
			vecini++;
	return vecini;
}

// COMPLEXITATE Θ(m)
void afvec_gnmm(const int *graf, int nrmuchii, int nod)
{
	int i;

	for (i = 0; i < nrmuchii; i++) {
		if (graf[i] == nod)
			printf(" %d;", graf[nrmuchii + i]);
		else if (graf[nrmuchii + i] == nod)
			printf(" %d;", graf[i]);
	}
	putchar('\n');
}

// COMPLEXITATE Θ(m)
bool muchie_gnmm(const int *graf, int nrmuchii, int nod1, int nod2)
{
	int i;

	if (nod1 > nod2) {			// nu sunt ordonate
		nod1 += nod2;
		nod2 = nod1 - nod2;		// nod2 <- nod1
		nod1 -= nod2;			// nod1 <- nod2
	}

	for (i = 0; i < nrmuchii; i++) {
		if (graf[i] == nod1 && graf[nrmuchii + i] == nod2)
			return true;
	}
	return false;
}

// COMPLEXITATE Θ(n+m²)#c
void vizlat_gnmm(const int *graf, int nrmuchii, int nod)
{
	int i, k, l, nrvarf;
	queue<int> qi;
	bool *vizitat;				// vizitat? A/F
	bool gasit;

	nrvarf = nrvarf_gnmm(graf, nrmuchii);
	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	vizitat[nod-1] = true;
	qi.push(nod);				// Q <= nod
	printf("   %d\n", nod);			// CALL vizitare(nod)

	while (!qi.empty()) {			// Q ≠ ∅
		k = qi.front();			// Q => k
		qi.pop();
		gasit = false;

		for (i = 0; i < nrmuchii; i++) {
			if (graf[i] == k)
				l = graf[nrmuchii + i];
			else if (graf[nrmuchii + i] == k)
				l = graf[i];
			else
				continue;
			if (vizitat[l-1])	// vârful a fost deja vizitat
				continue;
			vizitat[l-1] = true;
			qi.push(l);		// Q <= l
			printf(" → %d", l);	// CALL vizitare(l)
			gasit = true;
		}
		if (gasit)
			putchar('\n');
	}
	free(vizitat);
}

// COMPLEXITATE Θ(n+m²)#c
void vizad_gnmm(const int *graf, int nrmuchii, int nod)
{
	int i, k, l, nrvarf, adancime;
	stack<int> si;
	bool *vizitat;				// vizitat? A/F
	bool gasit, primul;

	nrvarf = nrvarf_gnmm(graf, nrmuchii);
	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	vizitat[nod-1] = true;
	si.push(nod);				// S <= nod
	printf("   %d", nod);			// CALL vizitare(nod)
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

		for (i = 0; i < nrmuchii; i++) {
			if (graf[i] == k)
				l = graf[nrmuchii + i];
			else if (graf[nrmuchii + i] == k)
				l = graf[i];
			else
				continue;
			if (vizitat[l-1])	// vârful a fost deja vizitat
				continue;
			vizitat[l-1] = true;
			si.push(k);		// S <= k
			if (primul) {
				printf("\n%*c", 4*adancime, ' ');
				primul = false;
			}
			printf(" → %d", l);	// CALL vizitare(l)
			k = l;
			adancime++;
			gasit = true;
			break;			// am găsit cel puțin un vârf nevizitat adiacent cu k
		}
	}
	putchar('\n');
	free(vizitat);
}
