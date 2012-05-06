/*
 * Operații comune la un graf neorientat indiferent de forma de reprezentare.
 * Funcții utilizate des în operațiile cu grafuri.
 */

//#define NDEBUG

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gn.h"

// COMPLEXITATE θ(n)
bool *mkviz(int nrvarf)
{
	int i;
	bool *viz;				// vizitat? A/F

	if (nrvarf <= 0)
		return NULL;

	viz = (bool *) malloc(sizeof(bool) * nrvarf);
	if (NULL == viz)
		return NULL;

	// inițial toate vârfurile sunt nevizitate
	for (i = 0; i < nrvarf; i++)
		viz[i] = false;
	return viz;
}

// timp θ(n+m) | spațiu θ(n+m)
int *gnla2ma(const struct nod graf[], int nrvarf)
{
	int i, j;
	int *mat;
	struct nod *elem;

	mat = (int *) calloc(nrvarf * nrvarf, sizeof(int));
	if (NULL == mat)
		return NULL;

	// parcurg lista de vecini
	for (i = 0; i < nrvarf; i++) {
		// verificare sanitară
		assert(1 <= graf[i].nr && graf[i].nr <= nrvarf);

		j = (graf[i].nr - 1) * nrvarf;	// început linie
		elem = graf[i].urm;
		while (NULL != elem) {
			mat[j + elem->nr - 1] = 1;
			elem = elem->urm;
		}
	}
	return mat;
}

// timp θ(n+m) | spațiu θ(n+m)
int *gnla2mm(const struct nod graf[], int nrvarf, int *nrmuchii)
{
	int i, j;
	int *mat;
	struct nod *elem;

	*nrmuchii = nrmuc_gnla(graf, nrvarf);
	printf("nrmuchii = %d\n", *nrmuchii);
	mat = (int *) calloc(*nrmuchii * 2, sizeof(int));
	if (NULL == mat)
		return NULL;

	// parcurg lista de vecini
	for (i = 0, j = 0; i < nrvarf; i++) {
		// verificare sanitară
		assert(1 <= graf[i].nr && graf[i].nr <= nrvarf);

		elem = graf[i].urm;
		while (NULL != elem) {
			if (graf[i].nr < elem->nr) {
				// verificare sanitară
				assert(j < *nrmuchii);
				mat[j] = graf[i].nr;
				mat[j + *nrmuchii] = elem->nr;
				++j;
			}
			elem = elem->urm;
		}
	}
	return mat;
}
