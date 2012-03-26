/*
 * Operații comune la un graf neorientat indiferent de forma de reprezentare.
 * Funcții utilizate des în operațiile cu grafuri.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "gn.h"

// alocă un vector de vizitare și inițializează cu "false"
bool *mkviz(int nrvarf)
{
	int i;
	bool *viz;				// un vector care reține doar starea vizitat? T/F

	if (nrvarf <= 0)
		return NULL;
	viz = (bool *) malloc(sizeof(bool) * nrvarf);
	if (NULL == viz)
		return NULL;
	for (i = 0; i < nrvarf; i++)		// inițial toate vârfurile sunt nevizitate
		viz[i] = false;
	return viz;
}
