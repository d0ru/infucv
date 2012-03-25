/*
 * Operații pe lista de muchii a unui graf neorientat.
 * Într-o matrice 2x|E| se păstrează lista de muchii.
 *
 * Lista de muchii se dă în felul următor:
 *   u1 u2 ... um
 *   v1 v1 ... vm
 * unde (u1,v1), (u2,v2),.. (um,vm) sunt toate muchiile grafului neorientat.
 */

#ifndef INFUCV_GNLM
#define INFUCV_GNLM
// GNLM - graf neorientat, listă de muchii

// nrmuchii = |E|, numărul muchiilor grafului neorientat
int *fcitire_gnlm(FILE *fisier, int *nrmuchii);

// citire de la STDIN
#define citire_gnlm(N)	fcitire_gnlm(stdin, N)

// afișare listă de muchii
void fafisare_gnlm(FILE *fisier, const int *matrice, int nrmuchii);

// afișare la STDOUT
#define afisare_gnlm(M,N)	fafisare_gnlm(stdout, M, N)

// returnează indexul maxim al tututor vârfurilor
int nrvarf_gnlm(const int *matrice, int nrmuchii);

// returnează numărul de vecini ai nodului dat
int nrvec_gnlm(const int *matrice, int nrmuchii, int nod);

// afișează toți vecinii nodului dat
void afvec_gnlm(const int *matrice, int nrmuchii, int nod);

// returnează true dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnlm(const int *matrice, int nrmuchii, int nod1, int nod2);

// parcurgere în lățime (BFS)
void vizlat_gnlm(const int *matrice, int nrmuchii, int nod);

// parcurgere în adâncime (DFS)
void vizad_gnlm(const int *matrice, int nrmuchii, int nod);
#endif
