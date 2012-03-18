/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnma.h"

// nrvarf = |V|, numărul vârfurilor grafului neorientat
int *fcitire_gnma(FILE *file, int *nrvarf)
{
	int i, j;
	int *matrice;

	fscanf(file, "%i", nrvarf);
	if (*nrvarf <= 0)
		return NULL;
	matrice = (int *) malloc(sizeof(int) * (*nrvarf) * (*nrvarf));
	if (NULL == matrice)
		return NULL;

	for (i = 0; i < *nrvarf; i++)
		for (j = 0; j < *nrvarf; j++)
			fscanf(stdin, "%d", matrice + i*(*nrvarf) + j);
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
