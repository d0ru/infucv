/*
 * Operații comune la un graf neorientat indiferent de forma de reprezentare.
 * Funcții utilizate des în operațiile cu grafuri.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "gn.h"

// COMPLEXITATE Θ(n)
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
