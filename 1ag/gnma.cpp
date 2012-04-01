/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între nodurile «i» și «j»
 */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gn.h"
#include "gnma.h"

#include <queue>
#include <stack>
using namespace std;

// n = |V|, numărul nodurilor grafului neorientat
// m = |E|, numărul muchiilor grafului neorientat
// c, numărul de componente conexe ale grafului neorientat

// COMPLEXITATE timp Θ(n²) | spațiu Θ(n²)
int *fcitire_gnma(FILE *fisier, int *nrvarf)
{
	int i, j;
	int *graf;				 // matricea de adiacență
	int *elem;

	if (1 != fscanf(fisier, "%i", nrvarf))
		return NULL;

	if (*nrvarf <= 0) {
		fprintf(stderr, "E: numărul de noduri «%d» trebuie să fie pozitiv!\n", *nrvarf);
		return NULL;
	}

	graf = (int *) malloc(sizeof(int) * (*nrvarf) * (*nrvarf));
						// |V|x|V|
	if (NULL == graf)
		return NULL;

	for (i = 0, elem = graf; i < *nrvarf; i++)
		for (j = 0; j < *nrvarf; j++, elem++)
			fscanf(fisier, "%d", elem);
	return graf;
}

// COMPLEXITATE timp Θ(n²) | spațiu Θ(n²)
void fafisare_gnma(FILE *fisier, const int *graf, int nrvarf)
{
	int i, j;

	for (i = 0; i < nrvarf; i++) {
		for (j = 0; j < nrvarf; j++)
			fprintf(fisier, " %d", graf[i*nrvarf + j]);
		fputc('\n', fisier);
	}
}

// COMPLEXITATE Θ(n)
int nrvec_gnma(const int *graf, int nrvarf, int nod)
{
	int i, vecini;

	vecini = 0;
	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	for (i = 0; i < nrvarf; i++)
		if (0 != graf[nod*nrvarf + i])
			vecini++;
	return vecini;
}

// COMPLEXITATE Θ(n)
void afvec_gnma(const int *graf, int nrvarf, int nod)
{
	int i;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	for (i = 0; i < nrvarf; i++)
		if (0 != graf[nod*nrvarf + i])
			printf(" %d;", i+1);
	putchar('\n');
}

// COMPLEXITATE Θ(1)
bool muchie_gnma(const int *graf, int nrvarf, int nod1, int nod2)
{
	// nodurile sunt numărate de la 1, nu de la 0
	if (0 != graf[(nod1 - 1)*nrvarf + nod2 - 1])
		return true;
	else
		return false;
}

// COMPLEXITATE Θ(n²)#c
void vizlat_gnma(const int *graf, int nrvarf, int nod)
{
	int i, k;
	queue<int> qi;
	bool *vizitat;				// vizitat? A/F
	bool gasit;

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	vizitat[nod] = true;
	qi.push(nod);				// Q <= nod
	printf("   %d\n", nod+1);		// CALL vizitare(nod)

	while (!qi.empty()) {			// Q ≠ ∅
		k = qi.front();			// Q => k
		qi.pop();
		gasit = false;
		for (i = 0; i < nrvarf; i++) {
			if (vizitat[i])		// nodul a fost deja vizitat
				continue;
			if (0 == graf[k*nrvarf + i])
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

// COMPLEXITATE Θ(n²)#c
void vizad_gnma(const int *graf, int nrvarf, int nod)
{
	int i, k, adancime;
	stack<int> si;
	bool *vizitat;				// vizitat? A/F
	bool gasit, primul;

	vizitat = mkviz(nrvarf);
	if (NULL == vizitat)
		return;

	nod--;					// nodurile sunt numărate de la 1, nu de la 0
	vizitat[nod] = true;
	si.push(nod);				// S <= nod
	printf("   %d", nod+1);			// CALL vizitare(nod)
	adancime = 2;				// primul în ierarhie

	gasit = false;				// dacă nodul curent mai are vecini nevizitați
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
			if (vizitat[i])		// nodul a fost deja vizitat
				continue;
			if (0 == graf[k*nrvarf + i])
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
			break;			// am găsit cel puțin un nod nevizitat adiacent cu k
		}
	}
	putchar('\n');
	free(vizitat);
}
