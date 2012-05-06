/*
 * Operații comune la un graf neorientat indiferent de forma de reprezentare.
 * Funcții utilizate des în operațiile cu grafuri.
 */

#include "gnla.h"
#include "gnma.h"
#include "gnmm.h"

#ifndef INFUCV_GN
#define INFUCV_GN
// GN - graf neorientat

// alocă un vector de vizitare și inițializează cu "false"
bool *mkviz(int nrvarf);

// conversii de reprezentare graf neorientat: LA ↦ MA, MM
int *gnla2ma(const struct nod graf[], int nrvarf);
int *gnla2mm(const struct nod graf[], int nrvarf, int *nrmuchii);

// conversii de reprezentare graf neorientat: MA ↦ LA, MM
struct nod *gnma2la(const int *graf, int nrvarf);
int *gnma2mm(const int *graf, int nrvarf, int *nrmuchii);

// conversii de reprezentare graf neorientat: MM ↦ LA, MA
struct nod *gnmm2la(const int *graf, int nrmuchii);
int *gnmm2ma(const int *graf, int nrmuchii);
#endif
