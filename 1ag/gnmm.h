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

#ifndef INFUCV_GNMM
#define INFUCV_GNMM
// GNMM - graf neorientat, matrice de muchii

// nrvarf = |V|, numărul nodurilor grafului neorientat
// (1 ≤ nod ≤ nrvarf)
// nrmuchii = |E|, numărul muchiilor grafului neorientat

// citire listă de muchii
int fcitire_gnmm(FILE *fisier, int **graf);
// citire de la STDIN
#define citire_gnmm(G)		fcitire_gnmm(stdin, G)

// afișare listă de muchii
void fafisare_gnmm(FILE *fisier, const int *graf, int nrmuchii);
// afișare la STDOUT
#define afisare_gnmm(G,M)	fafisare_gnmm(stdout, G,M)

// returnează numărul vârfurilor
int nrvarf_gnmm(const int *graf, int nrmuchii);

// returnează numărul de vecini ai nodului dat
int nrvec_gnmm(const int *graf, int nrmuchii, int nod);

// afișează toți vecinii nodului dat
void afvec_gnmm(const int *graf, int nrmuchii, int nod);

// returnează «true» dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnmm(const int *graf, int nrmuchii, int nod1, int nod2);

// parcurgere în lățime (BFS)
void vizlat_gnmm(const int *graf, int nrmuchii, int nod);

// parcurgere în adâncime (DFS)
void vizad_gnmm(const int *graf, int nrmuchii, int nod);
#endif
