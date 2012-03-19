/*
 * Operații pe lista de adiacență a unui graf neorientat.
 * Pentru fiecare nod se reține lista vecinilor săi într-o listă simplu
 * înlânțuită. Capul de listă pentru fiecare nod se reține într-un vector
 * de pointeri către structura «nod».
 *
 * Lista de adiacență se dă în felul următor:
 * nod: listă vecini 0
 */

#ifndef __GNLA__
#define __GNLA__
// GNLA - graf neorientat, listă de adiacență

struct nod {
	int nr;				// numărul vârfului în graf
	struct nod *urm;		// următorul nod vecin
};

// nrvarf = |V|, numărul vârfurilor grafului neorientat
struct nod *fcitire_gnla(FILE *fisier, int *nrvarf);

// citire de la STDIN
#define citire_gnla(N)	fcitire_gnla(stdin, N)

// afișare la STDOUT
void afisare_gnla(const struct nod varf[], int nrvarf);

// returnează numărul de vecini ai nodului dat
int nrvec_gnla(const struct nod varf[], int nrvarf, int nod);

// afișează toți vecinii nodului dat
void afvec_gnla(const struct nod varf[], int nrvarf, int nod);

// returnează true dacă nodurile sunt adiacente (formează o muchie)
bool muchie_gnla(const struct nod varf[], int nrvarf, int nod1, int nod2);
#endif
