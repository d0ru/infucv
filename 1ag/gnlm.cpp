/*
 * Operații pe lista de muchii a unui graf neorientat.
 * Într-o matrice 2x|E| se păstrează lista de muchii.
 *
 * Lista de muchii se dă în felul următor:
 *   u1 u2 ... um
 *   v1 v1 ... vm
 * unde (u1,v1), (u2,v2),.. (um,vm) sunt toate muchiile grafului neorientat.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnlm.h"

#include <queue>
#include <stack>
using namespace std;

// nrmuchii = |E|, numărul muchiilor grafului neorientat
int *fcitire_gnlm(FILE *fisier, int *nrmuchii)
{
	int i, m;
	int *matrice, *pi;

	fscanf(fisier, "%i", nrmuchii);
	if (*nrmuchii <= 0)
		return NULL;
	m = (*nrmuchii) * 2;
	matrice = (int *) calloc(m, sizeof(int));	// 2x|E|
	if (NULL == matrice)
		return NULL;

	pi = matrice;
	for (i = 0; i < m; i++)
		fscanf(fisier, "%d", pi++);
	return matrice;
}

// afișare listă de muchii
void fafisare_gnlm(FILE *fisier, const int *matrice, int nrmuchii)
{
	int i;

	for (i = 0; i < nrmuchii; i++)
		fprintf(fisier, " %d", matrice[i]);
	putchar('\n');
	for (i = 0; i < nrmuchii; i++)
		fprintf(fisier, " %d", matrice[nrmuchii + i]);
	putchar('\n');
}

// returnează indexul maxim al tututor vârfurilor
int nrvarf_gnlm(const int *matrice, int nrmuchii)
{
	int i, m, max;

	m = nrmuchii * 2;
	for (i = 0, max = 1; i < m; i++)
		if (matrice[i] > max)
			max = matrice[i];
	return max;
}

// returnează numărul de vecini ai nodului dat
int nrvec_gnlm(const int *matrice, int nrmuchii, int nod)
{
	int i, m, vecini;

	m = nrmuchii * 2;
	for (i = 0, vecini = 0; i < m; i++)
		if (matrice[i] == nod)
			vecini++;
	return vecini;
}

// afișează toți vecinii nodului dat
void afvec_gnlm(const int *matrice, int nrmuchii, int nod)
{
	int i;

	for (i = 0; i < nrmuchii; i++) {
		if (matrice[i] == nod)
			printf(" %d;", matrice[nrmuchii + i]);
		if (matrice[nrmuchii + i] == nod)
			printf(" %d;", matrice[i]);
	}
	putchar('\n');
}

// returnează true dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnlm(const int *matrice, int nrmuchii, int nod1, int nod2)
{
	int i;

	if (nod1 > nod2) {			// nu sunt ordonate
		nod1 += nod2;			// nod1 <- nod2
		nod2 = nod1 - nod2;		// nod2 <- nod1
		nod1 -= nod2;
	}
	for (i = 0; i < nrmuchii; i++) {
		if (matrice[i] == nod1 && matrice[nrmuchii + i] == nod2)
			return true;
	}
	return false;
}

// parcurgere în lățime (BFS)
void vizlat_gnlm(const int *matrice, int nrmuchii, int nod)
{
	int i, k, l, nrvarf;
	queue<int> qi;
	bool *vizitat;				// un vector care reține doar starea vizitat? T/F
	bool gasit;

	nrvarf = nrvarf_gnlm(matrice, nrmuchii);
	vizitat = (bool *) malloc(sizeof(bool) * nrvarf);
	if (NULL == vizitat)
		return;
	for (i = 0; i < nrvarf; i++)		// inițial toate vârfurile sunt nevizitate
		vizitat[i] = false;

	vizitat[nod-1] = true;
	qi.push(nod);				// Q <= nod
	printf("   %d\n", nod);			// CALL vizitare(nod)

	while (!qi.empty()) {			// Q ≠ ∅
		k = qi.front();			// Q => k
		qi.pop();
		gasit = false;

		for (i = 0; i < nrmuchii; i++) {
			if (matrice[i] == k)
				l = matrice[nrmuchii + i];
			else if (matrice[nrmuchii + i] == k)
				l = matrice[i];
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

// parcurgere în adâncime (DFS)
void vizad_gnlm(const int *matrice, int nrmuchii, int nod)
{
	int i, k, l, nrvarf, adancime;
	stack<int> si;
	bool *vizitat;				// un vector care reține doar starea vizitat? T/F
	bool gasit, primul;

	nrvarf = nrvarf_gnlm(matrice, nrmuchii);
	vizitat = (bool *) malloc(sizeof(bool) * nrvarf);
	if (NULL == vizitat)
		return;
	for (i = 0; i < nrvarf; i++)		// inițial toate vârfurile sunt nevizitate
		vizitat[i] = false;


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
			if (matrice[i] == k)
				l = matrice[nrmuchii + i];
			else if (matrice[nrmuchii + i] == k)
				l = matrice[i];
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
