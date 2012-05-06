/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între nodurile «i» și «j»
 */

#ifndef INFUCV_GNMA
#define INFUCV_GNMA
// GNMA - graf neorientat, matrice de adiacență

// nrvarf = |V|, numărul nodurilor grafului neorientat
// (1 ≤ nod ≤ nrvarf)

// citire matrice de adiacență
int fcitire_gnma(FILE *fisier, int **graf);
// citire de la STDIN
#define citire_gnma(G)		fcitire_gnma(stdin, G)

// citire matrice de adiacență
void fafisare_gnma(FILE *fisier, const int *graf, int nrvarf);
// afișare la STDOUT
#define afisare_gnma(G,N)	fafisare_gnma(stdout, G, N)

// returnează numărul de vecini ai nodului dat
int nrvec_gnma(const int *graf, int nrvarf, int nod);

// afișează toți vecinii nodului dat
void afvec_gnma(const int *graf, int nrvarf, int nod);

// returnează «true» dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnma(const int *graf, int nrvarf, int nod1, int nod2);

// parcurgere în lățime (BFS)
void vizlat_gnma(const int *graf, int nrvarf, int nod);

// parcurgere în adâncime (DFS)
void vizad_gnma(const int *graf, int nrvarf, int nod);

// determină un ciclu eulerian (v0 = nod = vn)
void rosenstiehl_gnma(const int *graf, int nrvarf, int nod);
#endif
