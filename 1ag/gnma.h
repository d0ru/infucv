/*
 * Operații cu matricea de adiacență a unui graf neorientat.
 * a[i,j] = 0 dacă NU există o muchie între vârfurile i și j
 */

#ifndef __GNMA__
#define __GNMA__
// GNMA - graf neorientat, matrice de adiacență
// nrvarf = |V|, numărul vârfurilor grafului neorientat
int *fcitire_gnma(FILE *file, int *nrvarf);

// citire de la STDIN
#define citire_gnma(N)	fcitire_gnma(stdin, N)

// afișare la STDOUT
void afisare_gnma(const int *matrice, int nrvarf);

// returnează numărul de vecini ai nodului dat
int nrvec_gnma(const int *matrice, int nrvarf, int nod);

// afișează toți vecinii nodului dat
void afvec_gnma(const int *matrice, int nrvarf, int nod);

// returnează true dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnma(const int *matrice, int nrvarf, int nod1, int nod2);
#endif
