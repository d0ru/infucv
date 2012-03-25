/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnma.h"

#include <queue>
#include <stack>
using namespace std ;

// nrvarf = |V|, numărul vârfurilor grafului neorientat
int *fcitire_gnma(FILE *fisier, int *nrvarf)
{
	int i, j;
	int *matrice;

	fscanf(fisier, "%i", nrvarf);
	if (*nrvarf <= 0)
		return NULL;
	matrice = (int *) malloc(sizeof(int) * (*nrvarf) * (*nrvarf));
	if (NULL == matrice)
		return NULL;

	for (i = 0; i < *nrvarf; i++)
		for (j = 0; j < *nrvarf; j++)
			fscanf(fisier, "%d", matrice + i*(*nrvarf) + j);
	return matrice;
}

// afișare la STDOUT
void afisare_gnma(const int *matrice, int nrvarf)
{
	int i, j;

	for (i = 0; i < nrvarf; i++) {
		for (j = 0; j < nrvarf; j++)
			printf(" %d", matrice[i*nrvarf + j]);
		putchar('\n');
	}
}

// returnează numărul de vecini ai nodului dat
int nrvec_gnma(const int *matrice, int nrvarf, int nod)
{
	int i, vecini;

	vecini = 0;
	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	for (i = 0; i < nrvarf; i++)
		if (0 != matrice[nod*nrvarf + i])
			vecini++;
	return vecini;
}

// afișează toți vecinii nodului dat
void afvec_gnma(const int *matrice, int nrvarf, int nod)
{
	int i;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	for (i = 0; i < nrvarf; i++)
		if (0 != matrice[nod*nrvarf + i])
			printf(" %d;", i+1);
	putchar('\n');
}

// returnează true dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnma(const int *matrice, int nrvarf, int nod1, int nod2)
{
	nod1--;					// nodurile sunt numărate de la 1, nu de la 0
	nod2--;
	if (0 != matrice[nod1*nrvarf + nod2])
		return true;
	else
		return false;
}

// parcurgere în lățime (BFS)
void vizlat_gnma(const int *matrice, int nrvarf, int nod)
{
	int i, k;
	queue<int> qi;
	bool *vizitat;				// un vector care reține doar starea vizitat? T/F
	bool gasit;

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
	printf("   %d\n", nod+1);			// CALL vizitare(nod)

	while (!qi.empty()) {			// Q ≠ ∅
		k = qi.front();			// Q => k
		qi.pop();
		gasit = false;
		for (i = 0; i < nrvarf; i++) {
			if (vizitat[i])		// vârful a fost deja vizitat
				continue;
			if (0 == matrice[k*nrvarf + i])
				continue;	// nu există o muchie (k;i)
			vizitat[i] = true;
			qi.push(i);		// Q <= i
			printf(" → %d", i+1);	// CALL vizitare(i)
			gasit = true;
		}
		if (gasit)
			putchar('\n');
	}
	free(vizitat);
}

// parcurgere în adâncime (DFS)
void vizad_gnma(const int *matrice, int nrvarf, int nod)
{
	int i, k, adancime;
	stack<int> si;
	bool *vizitat;				// un vector care reține doar starea vizitat? T/F
	bool gasit, primul;

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
		for (i = 0; i < nrvarf; i++) {
			if (vizitat[i])		// vârful a fost deja vizitat
				continue;
			if (0 == matrice[k*nrvarf + i])
				continue;	// nu există o muchie (k;i)
			vizitat[i] = true;
			si.push(k);		// S <= k
			if (primul) {
				printf("\n%*c", 4*adancime, ' ');
				primul = false;
			}
			printf(" → %d", i+1);	// CALL vizitare(i)
			k = i;
			adancime++;
			gasit = true;
			break;			// am găsit cel puțin un vârf nevizitat adiacent cu k
		}
	}
	putchar('\n');
	free(vizitat);
}
